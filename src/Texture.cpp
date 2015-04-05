#include "../include/Texture.h"

Texture::Texture(int w, int h, unsigned char* data, int target, int filter, int internalFmt, int format, bool clamp, int attachment)
{
    init(w, h, data, target, filter, internalFmt, format, clamp, attachment, "");
}

Texture::Texture(const std::string filename, int target, int filter)
{
	this->filename = filename;
	this->filter = filter;

    int w, h, comp;
    unsigned char* data = ImageLoader::loadRawDataFromFile(filename.c_str(), &w, &h, &comp);
    if (data != NULL)
    {
        init(w, h, data, target, filter, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0, filename);
        ImageLoader::free_data(data);
    }
}

void Texture::init(int w, int h, unsigned char *data, int target, int filter, int internalFmt, int format, bool clamp, int attachment, std::string filename)
{
    this->filename = filename;
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
            this->m_resource = new imageResource(target, w, h, 1,
                                                 data, filter,
                                                 internalFmt, format,
                                                 false, attachment);
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
        vertex(vec3(-1.0f * w2, -1.0f * h2, 0.0f), vec2(0.0f, 0.0f)),
        vertex(vec3( 1.0f * w2, -1.0f * h2, 0.0f), vec2(1.0f, 0.0f)),
        vertex(vec3( 1.0f * w2,  1.0f * h2, 0.0f), vec2(1.0f, 1.0f)),
        vertex(vec3(-1.0f * w2,  1.0f * h2, 0.0f), vec2(0.0f, 1.0f))
    };
    std::vector<int> ind = {
        0,1,2,3
    };
    m_quad->addVertices(verts, ind);
}

Texture::Texture(const Texture& texture)
	: m_resource(texture.m_resource), filename(texture.filename)
{
	m_resource->addReference();
}

Texture::Texture(std::string filename) : Texture(filename, GL_TEXTURE_2D, GL_LINEAR)
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
}

void Texture::setFilter(int val)
{
    if (!m_resource) return;
    filter = val;
    m_resource->setFilter(filter);
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
