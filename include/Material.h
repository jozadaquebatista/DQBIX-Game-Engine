// File: Material.h
// Class: Material
// Author: Diego Lopes <diego95lopes@live.com>
// 21/03/2015
#ifndef __NIX_MATERIAL__
#define __NIX_MATERIAL__
#pragma once

#include "shader.h"
#include "Texture.h"
class Material
{
public:
	Material();
	Material(Texture* diffuse);
	Material(Texture* diffuse, Texture* normal);

	virtual ~Material();

	Texture* getDiffuseTexture() const { return m_diffuse; }
	void setDiffuseTexture(Texture* tex) { m_diffuse = tex; }
	Texture* getNormalTexture() const { return m_normal; }
	void setNormalTexture(Texture* tex) { m_normal = tex; }

private:
	float dR, dG, dB, dA;
	float m_normal_power;
	Texture* m_diffuse;
	Texture* m_normal;
	Shader* m_matshader;
};

#endif // __NIX_MATERIAL__