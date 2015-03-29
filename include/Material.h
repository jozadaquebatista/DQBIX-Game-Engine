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

    float getSpecularPower() const;
    void setSpecularPower(float getSpecularPower);

    float getNormalPower() const;
    void setNormalPower(float getNormalPower);

    bool getIsSshadeless() const;
    void setShadeless(bool getIsSshadeless);

    void setDiffuseColor(float r, float g, float b, float a);
    void setSpecularColor(float r, float g, float b, float a);

    float dR, dG, dB, dA;
    float sR, sG, sB, sA;

    static Texture* DefaultNormal;
private:
    Material(Material&& mat) {}
    void operator=(Material mat) {}

    float m_specularPower;
    float m_normalPower;
    bool m_shadeless;

	Texture* m_diffuse;
    Texture* m_normal;
};

#endif // __NIX_MATERIAL__
