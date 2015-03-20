#include "../include/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

// TODO: Simplify this
Texture::Texture(int w, int h, unsigned char* data, int target, int filter, int internalFmt, int format, bool clamp, int attachment)
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

void Texture::create_mesh()
{
	float w2 = (float)getWidth() / 2.0f;
	float h2 = (float)getHeight() / 2.0f;

	m_quad = new Mesh();
	std::vector<vertex> verts = {
		vertex(vec3(-1.0f * w2, -1.0f * h2, 0.0f), vec2(0.0f, 1.0f)),
		vertex(vec3(-1.0f * w2,  1.0f * h2, 0.0f), vec2(0.0f, 0.0f)),
		vertex(vec3( 1.0f * w2, -1.0f * h2, 0.0f), vec2(1.0f, 0.0f)),
		vertex(vec3( 1.0f * w2,  1.0f * h2, 0.0f), vec2(1.0f, 1.0f))
	};
	std::vector<int> ind = {
		0, 1, 2,
		1, 2, 3
	};
	m_quad->addVertices(verts, ind);
}

// TODO: Simplify this
Texture::Texture(const std::string filename, int target, int filter)
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

Texture::Texture(const Texture& texture)
	: m_resource(texture.m_resource), filename(texture.filename)
{
	m_resource->addReference();
}

Texture::Texture(std::string filename) : Texture(filename, GL_TEXTURE_2D, GL_NEAREST)
{

}

void Texture::operator=(Texture texture)
{
	char *temp[sizeof(Texture) / sizeof(char)];
	memcpy(temp, this, sizeof(Texture));
	memcpy(this, &texture, sizeof(Texture));
	memcpy(&texture, temp, sizeof(Texture));
}

Texture::~Texture()
{
	if (m_resource && m_resource->removeReference())
	{
		if (filename.length() > 0)
			m_loadedImages.erase(filename);

		SAFE_DELETE(m_resource);
	}
	SAFE_DELETE(m_quad);
}

void Texture::useAsRenderTarget()
{
	m_resource->useAsRenderTarget();
}

void Texture::bind()
{
	this->use(0);
}

void Texture::use(int sampler_slot)
{
	assert(sampler_slot >= 0 && sampler_slot <= 31);
	glActiveTexture(GL_TEXTURE0 + sampler_slot);
	m_resource->use();
}

// Thanks to this tutorial <http://immersedcode.org/2011/4/7/stb-image/>
SDL_Surface* Texture::loadicon(const char* filename)
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
