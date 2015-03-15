#ifndef __IX_IMAGE__
#define __IX_IMAGE__
#pragma once

#include <map>
#include <string>
#include <assert.h>

#include "imageResource.h"
#include "sdl_backend.h"
#include "Matrices.h"
#include "color.h"

typedef struct  
{
	int x, y, w, h;
} rect;

class image
{
public:
	image(const image& texture);
	void operator=(image texture);

	image(int w, int h, unsigned char* data = 0, int target = GL_TEXTURE_2D, int filter = GL_LINEAR, int internalFmt = 0,
		  int format = 0, bool clamp = false, int attachment = 0);
	image(const std::string filename, int target, int filter);

	image(std::string filename);

	virtual ~image();

	int getFilter() const { return filter; }
	void setFilter(int val) { filter = val; }

	void setAsRenderTarget();
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

	imageResource* getResource() const { return m_resource; }
	
	void draw_full(int x, int y, float sx, float sy, float a);

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
		.beginClass<image>("image")
		.addConstructor<void(*)(std::string)>()
		.addProperty("filter", &image::getFilter, &image::setFilter)
		.addFunction("setAsRenderTarget", &image::setAsRenderTarget)
		.addFunction("bind", &image::bind)
		.addFunction("use", &image::use)
		.addProperty("width", &image::getWidth)
		.addProperty("height", &image::getHeight)
		.endClass();
			
		imageResource::lua_reg(L);
	}
	Matrix4 m;
	// *sighs*
	static SDL_Surface* loadicon(const char* filename);
private:
	std::map<std::string, imageResource*> m_loadedImages;
	imageResource* m_resource;
	std::string filename;
	int filter;
	rect cliprect;

	float* vbo_verts;
	GLuint vbo, ebo;

	void create_vbo();
};

#endif //__IX_IMAGE__