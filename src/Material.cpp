#include "..\include\Material.h"


Material::Material()
{
    m_diffuse = NULL;
    m_normal = NULL;

    sR = sG = sB = sA = dR = dG = dB = dA = 1.0f;
    m_specularPower = 1.0f;
    m_normalPower = 1.0f;
    m_shadeless = false;
    m_specularHardness = 1.0f;
}

Material::Material(Texture* diffuse) : Material()
{
	m_diffuse = diffuse;
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
float Material::getSpecularHardness() const
{
    return m_specularHardness;
}

void Material::setSpecularHardness(float specularHardness)
{
    m_specularHardness = specularHardness;
}




