#include "..\include\Material.h"


Material::Material()
{
	m_diffuse = nullptr;
	m_normal = nullptr;

	m_matshader = new Shader();
	
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
	SAFE_DELETE(m_matshader);
	SAFE_DELETE(m_diffuse);
	SAFE_DELETE(m_normal);
}
