#ifndef __IX_IMG_RES__
#define __IX_IMG_RES__
#pragma once

#include "graphics.h"
#include <string>
#include "lua.hpp"

class imageResource
{
public:

	imageResource(int target=0,
				  int width=1,
				  int height=1,
				  int numtex=1,
				  unsigned char* data=0,
				  int filter=0,
				  int internalFormat=0,
				  int format=0,
				  bool clamp=false,
				  int attachment=0);

	virtual ~imageResource();

	void initTextures(unsigned char* data,
					  int filter,
					  int internalFormat,
					  int format,
					  bool clamp);
	void initRenderTargets(int attachment);

	int getTarget() const { return m_target; }

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	void use();
	void useAsRenderTarget();

	void addReference();
	bool removeReference();
	
	GLuint getID();

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<imageResource>("imageResource")
			.addProperty("width", &imageResource::getWidth)
			.addProperty("height", &imageResource::getHeight)
			.addProperty("target", &imageResource::getTarget)
			.addFunction("use", &imageResource::use)
			.addFunction("useAsRenderTarget", &imageResource::useAsRenderTarget)
			.addFunction("addReference", &imageResource::addReference)
			.addFunction("removeReference", &imageResource::removeReference)
			.addFunction("id", &imageResource::getID)
			.endClass();
	}
private:
	GLuint m_id;
	int m_fbo;
	int m_numTextures;
	int m_refCount;
	int m_target;
	
	int m_width, m_height;
	
	int* genTextures(int count);

    imageResource(imageResource&) {}
    void operator=(imageResource) {}
};

#endif //__IX_IMG_RES__
