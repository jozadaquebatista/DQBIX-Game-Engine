#ifndef __IX_TEXTURE__
#define __IX_TEXTURE__
#pragma once

#include <map>
#include <string>
#include <assert.h>

#include "imageResource.h"
#include "sdl_backend.h"
#include "color.h"
#include "mesh.h"
#include "shader.h"
#include "point.hpp"
#include "shaders.h"

#include "lua.hpp"

#include "imageloader.h"

typedef struct  
{
	int x, y, w, h, frame, cols, rows;
} rect;

class Texture
{
public:
	Texture(const Texture& texture);
	void operator=(Texture texture);

    Texture(int w, int h,
            unsigned char* data = 0,
            int target = GL_TEXTURE_2D,
            int filter = GL_LINEAR,
            int internalFmt = 0,
            int format = 0,
            bool clamp = false,
            int attachment = 0);
	Texture(const std::string filename, int target, int filter);

	Texture(std::string filename);

	virtual ~Texture();

	int getFilter() const { return filter; }
    void setFilter(int val);

	void useAsRenderTarget();
	void bind();
	void use(int sampler_slot);

	int id() const
	{
		return getResource()->getID();
	}

	int getWidth() const { return getCliprect().w; }
	int getHeight() const { return getCliprect().h; }

	rect getCliprect() const { return cliprect; }
	void setCliprect(rect val) { cliprect = val; }

    // For sprite animation and tilemaps
	inline vec4 getTransformedClipRect()
	{
		float crw = (float)getCliprect().w / (float)getResource()->getWidth();
		float crh = (float)getCliprect().h / (float)getResource()->getHeight();
		float crx = (float)getCliprect().x / (float)getResource()->getWidth();
		float cry = (float)getCliprect().y / (float)getResource()->getHeight();

        return vec4(crx * getCliprect().cols, cry * getCliprect().rows, crw, crh);
	}

	Mesh* getShape() const { return m_quad; }

	imageResource* getResource() const { return m_resource; }

	static void RegisterObject(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<Texture>("Texture")
			.addConstructor<void(*)(std::string)>()
			.addProperty("width", &Texture::getWidth)
			.addProperty("height", &Texture::getHeight)
			.endClass();
	}

private:
	std::map<std::string, imageResource*> m_loadedImages;
	imageResource* m_resource;
	std::string filename;
	int filter;
	rect cliprect;
	
	Mesh* m_quad;
	void create_mesh();

    void init(int w, int h,
              unsigned char* data = 0,
              int target = GL_TEXTURE_2D,
              int filter = GL_LINEAR,
              int internalFmt = 0,
              int format = 0,
              bool clamp = false,
              int attachment = 0,
              std::string filename = "");
};

#endif //__IX_IMAGE__
