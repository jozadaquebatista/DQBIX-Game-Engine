#include "../include/image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

// TODO: Simplify this
image::image(int w, int h, unsigned char* data, int target, int filter, int internalFmt, int format, bool clamp, int attachment)
{
	this->filename = "RENDERTEXTURE" + w + h + m_loadedImages.size();
	std::map<std::string, imageResource*>::const_iterator pos = m_loadedImages.find(filename);
	if (pos == m_loadedImages.end())
	{
		this->m_resource = new imageResource(target, w, h, 1, data,
			filter, internalFmt, format, false, attachment);
		m_loadedImages.insert({ filename, m_resource });
	}
	else
	{
		imageResource* oldres = pos->second;
		if (oldres != NULL)
		{
			m_resource = oldres;
			m_resource->addReference();
		}
		else
		{
			this->m_resource = new imageResource(target, w, h, 1, data,
				filter, internalFmt, format, false, attachment);
			m_loadedImages.insert({ filename, m_resource });
		}
	}

	cliprect.x = 0;
	cliprect.y = 0;
	cliprect.w = m_resource->getWidth();
	cliprect.h = m_resource->getHeight();
	cliprect.cols = 1;
	cliprect.rows = 1;

	create_mesh();
	
}

void image::create_mesh()
{
	m_quad = new mesh();
	std::vector<vertex> verts = {
		vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)),
		vertex(vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),
		vertex(vec3(0.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
		vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)),
		vertex(vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)),
		vertex(vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f))
	};
	m_quad->addVertices(verts);

	m_shader = new shader();
	m_shader->fromString(default_vert, default_frag);

	m_shader->compile();
	m_shader->addCommonUniforms();
	m_shader->addUniform("image");
	m_shader->addUniform("cliprect");
}

// TODO: Simplify this
image::image(const std::string filename, int target, int filter)
{
	this->filename = filename;
	this->filter = filter;

	std::map<std::string, imageResource*>::const_iterator pos = m_loadedImages.find(filename);
	if (pos == m_loadedImages.end())
	{
		int w, h, comp;
		unsigned char* data = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb_alpha);
		if (data == nullptr)
		{
			printf("%s\n", "Failed to load image.");
			exit(EXIT_FAILURE);
		}

		this->m_resource = new imageResource(target, w, h, 1, data,
			filter, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0);
		m_loadedImages.insert({ filename, m_resource });

		stbi_image_free(data);
	}
	else
	{
		imageResource* oldres = pos->second;
		if (oldres != NULL)
		{
			m_resource = oldres;
			m_resource->addReference();
		}
		else
		{
			int w, h, comp;
			unsigned char* data = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb_alpha);
			if (data == nullptr)
			{
				printf("%s\n", "Failed to load image.");
				exit(EXIT_FAILURE);
			}

			this->m_resource = new imageResource(target, w, h, 1, data,
				filter, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0);
			m_loadedImages.insert({ filename, m_resource });

			stbi_image_free(data);
		}
	}

	cliprect.x = 0;
	cliprect.y = 0;
	cliprect.w = m_resource->getWidth();
	cliprect.h = m_resource->getHeight();
	cliprect.cols = 1;
	cliprect.rows = 1;

	create_mesh();
}

image::image(const image& texture) :
m_resource(texture.m_resource),
filename(texture.filename)
{
	m_resource->addReference();
}

image::image(std::string filename) : image(filename, GL_TEXTURE_2D, GL_NEAREST)
{

}

void image::operator=(image texture)
{
	char *temp[sizeof(image) / sizeof(char)];
	memcpy(temp, this, sizeof(image));
	memcpy(this, &texture, sizeof(image));
	memcpy(&texture, temp, sizeof(image));
}

image::~image()
{
	if (m_resource && m_resource->removeReference())
	{
		if (filename.length() > 0)
			m_loadedImages.erase(filename);

		delete m_resource;
	}
	if (m_shader) delete m_shader;
	if (m_quad) delete m_quad;
}

void image::setAsRenderTarget()
{
	m_resource->useAsRenderTarget();
}

void image::bind()
{
	this->use(0);
}

void image::use(int sampler_slot)
{
	assert(sampler_slot >= 0 && sampler_slot <= 31);
	glActiveTexture(GL_TEXTURE0 + sampler_slot);
	m_resource->use();
}

void image::draw_full(int x, int y, float sx, float sy, float a, mat4 proj)
{
	int w = getCliprect().w;
	int h = getCliprect().h;

	float crw = (float)getCliprect().w / (float)getResource()->getWidth();
	float crh = (float)getCliprect().h / (float)getResource()->getHeight();
	float crx = (float)getCliprect().x / (float)getResource()->getWidth();
	float cry = (float)getCliprect().y / (float)getResource()->getHeight();

	float px = (float)x / (float)w;
	float py = (float)y / (float)h;
	float sw = w * sx;
	float sh = h * sy;

	float ox = sw * origin.x;
	float oy = sh * origin.y;

	// Model matrix
	m = mat4(1.0f);
	m = translate(m, vec3((float)x, (float)y, 0.0f));
	m = translate(m, vec3(ox, oy, 0.0f));	
	m = rotate(m, a, vec3(0.0f, 0.0f, 1.0f));	
	m = translate(m, vec3(-ox, -oy, 0.0f));
	m = scale(m, vec3(sw, sh, 1.0f));
	
	// Bind texture
	bind();

	// Use shader
	if (m_shader != nullptr)
	{
		m_shader->use();
		m_shader->setInt("image", 0);
		m_shader->setVec4("cliprect", crx * cliprect.cols, cry * cliprect.rows, crw, crh);
		m_shader->setMatrix("model", m);
		m_shader->setMatrix("proj", proj);
	}

	// Draw a quad
	m_quad->draw();

	glUseProgram(0);

}

// Thanks to this tutorial <http://immersedcode.org/2011/4/7/stb-image/>
SDL_Surface* image::loadicon(const char* filename)
{
	int x, y, comp;
	unsigned char *data;
	uint32_t rmask, gmask, bmask, amask;
	SDL_Surface *rv;

	FILE *file = fopen(filename, "rb");
	if (!file)
		return 0;

	data = stbi_load_from_file(file, &x, &y, &comp, 0);
	fclose(file);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	if (comp == 4) {
		rv = SDL_CreateRGBSurface(0, x, y, 32, rmask, gmask, bmask, amask);
	}
	else if (comp == 3) {
		rv = SDL_CreateRGBSurface(0, x, y, 24, rmask, gmask, bmask, 0);
	}
	else {
		stbi_image_free(data);
		return 0;
	}

	memcpy(rv->pixels, data, comp * x * y);
	stbi_image_free(data);

	return rv;
}
