#include "../include/Material.h"

Texture* Material::DefaultNormal = 0;

Material::Material()
{
    m_diffuse = NULL;
    m_normal = NULL;

    sR = sG = sB = sA = dR = dG = dB = dA = 1.0f;
    m_specularPower = 1.0f;
    m_normalPower = 1.0f;
    m_shadeless = false;

    // Default normal texture
    unsigned char* data = new unsigned char[2 * 2 * 4];
    for (int i = 0; i < 2 * 2 * 4; i += 4)
    {
        data[i]      = (unsigned char)128; // R
        data[i + 1]  = (unsigned char)127; // G
        data[i + 2]  = (unsigned char)254; // B
        data[i + 3]  = (unsigned char)255; // A
    }
    Material::DefaultNormal = new Texture(2, 2, data, GL_TEXTURE_2D,
                                          GL_NEAREST, GL_RGBA, GL_RGBA,
                                          false, GL_COLOR_ATTACHMENT0);
}

Material::Material(Texture* diffuse) : Material()
{
	m_diffuse = diffuse;
    m_normal = Material::DefaultNormal;
}

Material::Material(Texture* diffuse, Texture* normal) : Material(diffuse)
{
	m_normal = normal;
}

Material::~Material()
{
	SAFE_DELETE(m_diffuse);
	SAFE_DELETE(m_normal);
}
float Material::getSpecularPower() const
{
    return m_specularPower;
}

void Material::setSpecularPower(float specularPower)
{
    m_specularPower = specularPower;
}
float Material::getNormalPower() const
{
    return m_normalPower;
}

void Material::setNormalPower(float normalPower)
{
    m_normalPower = normalPower;
}
bool Material::getIsSshadeless() const
{
    return m_shadeless;
}

void Material::setShadeless(bool shadeless)
{
    m_shadeless = shadeless;
}

void Material::setDiffuseColor(float r, float g, float b, float a)
{
    dR = r;
    dG = g;
    dB = b;
    dA = a;
}

void Material::setSpecularColor(float r, float g, float b, float a)
{
    sR = r;
    sG = g;
    sB = b;
    sA = a;
}
