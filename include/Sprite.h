// File: Sprite.h
// Class: Sprite
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_SPRITE__
#define __NIX_SPRITE__
#pragma once

#include "Node.h"
#include "collisiondetection.h"
#include "Material.h"

class Sprite : public Node
{
public:
    Sprite();
	Sprite(std::string filename);
    Sprite(std::string filename, std::string normal_filename);
    Sprite(Texture* diff);
    Sprite(Texture* diff, Texture* norm);

	virtual ~Sprite();

    void draw(SceneTree* tree);
    bool hovered(point mousepos);

	static void RegisterObject(lua_State* L);

    Material* getMaterial() const;
    void setMaterial(Material *material);

private:
    Material* m_material;
    Shader* m_shader;

    void load_shader();
};

#endif //__NIX_SPRITE__
