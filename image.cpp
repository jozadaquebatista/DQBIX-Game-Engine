#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

image::image(int w, int h, unsigned char* data, int target, int filter, int internalFmt, int format, bool clamp, int attachment)
{
	glEnable(GL_TEXTURE_2D);
	this->filename = "RENDERTEXTURE" + w + h + m_loadedImages.size();
	std::map<std::string, imageResource*>::const_iterator pos = m_loadedImages.find(filename);
	if (pos == m_loadedImages.end())
	{
		m_resource = new imageResource(GL_TEXTURE_2D, w, h,
			1, new unsigned char*[] {data}, new int[] {filter}, new int[] {internalFmt},
			new int[] {format}, clamp, new int[] {attachment});
		m_loadedImages[filename] = m_resource;
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
			m_resource = new imageResource(GL_TEXTURE_2D, w, h,
				1, new unsigned char*[] {data}, new int[] {filter}, new int[] {internalFmt},
				new int[] {format}, clamp, new int[] {attachment});
			m_loadedImages[filename] = m_resource;
		}
	}
	glDisable(GL_TEXTURE_2D);

	cliprect.x = 0;
	cliprect.y = 0;
	cliprect.w = m_resource->getWidth();
	cliprect.h = m_resource->getHeight();

	create_vbo();
}

image::image(const std::string filename, int target, int filter)
{
	glEnable(GL_TEXTURE_2D);
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

		this->m_resource = new imageResource(target, w, h, 1, new unsigned char*[]{data},
			new int[] {filter}, new int[] {GL_RGBA},
			new int[] {GL_RGBA}, false, new int[] {GL_COLOR_ATTACHMENT0});
		m_loadedImages[filename] = m_resource;

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

			this->m_resource = new imageResource(target, w, h, 1, new unsigned char*[]{data},
				new int[] {filter}, new int[] {GL_RGBA},
				new int[] {GL_RGBA}, false, new int[] {GL_COLOR_ATTACHMENT0});
			m_loadedImages[filename] = m_resource;

			stbi_image_free(data);
		}
	}
	glDisable(GL_TEXTURE_2D);
	cliprect.x = 0;
	cliprect.y = 0;
	cliprect.w = m_resource->getWidth();
	cliprect.h = m_resource->getHeight();

	create_vbo();
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
	if (vbo) glDeleteBuffers(1, &vbo);
	if (ebo) glDeleteBuffers(1, &ebo);
}

void image::setAsRenderTarget()
{
	m_resource->useAsRenderTarget();
}

void image::bind()
{
	m_resource->use(0);
}

void image::use(int sampler_slot)
{
	assert(sampler_slot >= 0 && sampler_slot <= 31);
	glActiveTexture(GL_TEXTURE0 + sampler_slot);
	m_resource->use(0);
}

void image::make_transparent(color* key)
{
	unsigned char* ndata = new unsigned char[m_resource->getWidth() * m_resource->getHeight() * 4];
	int j = 0;
	for (int i = 0; i < m_resource->getWidth() * m_resource->getHeight() * 3; i+=3)
	{
		ndata[j] = m_resource->getData()[0][i];
		ndata[j+1] = m_resource->getData()[0][i+1];
		ndata[j+2] = m_resource->getData()[0][i+2];

		if (m_resource->getData()[0][i]     == 255 * key->r &&
			m_resource->getData()[0][i + 1] == 255 * key->g &&
			m_resource->getData()[0][i + 2] == 255 * key->b)
			ndata[i + 3] = 0;
		else
			ndata[i + 3] = 1;
	}

	int w = m_resource->getWidth();
	int h = m_resource->getHeight();
	int target = m_resource->getTarget();

	delete m_resource;
	m_resource = new imageResource(target, w, h, 1, new unsigned char*[]{ndata},
		new int[] {filter}, new int[] {GL_RGBA},
		new int[] {GL_RGBA}, false, new int[] {GL_COLOR_ATTACHMENT0});
	m_loadedImages[filename] = m_resource;
	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	stbi_image_free(ndata);
}

void image::draw_full(int x, int y, float sx, float sy, float a)
{
	glPushMatrix();

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

	m.identity();
	m.rotateZ(a).scale(sw, sh, 1.0f).translate(x, y, 0);
	
	glEnable(GL_TEXTURE_2D);
	bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

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

void image::create_vbo()
{
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	float vertices[] = {
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f
	};
	int indices[] = {
		0, 1, 2, 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(int), indices, GL_STATIC_DRAW);

}
