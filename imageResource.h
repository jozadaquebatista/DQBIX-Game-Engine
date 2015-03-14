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
				  unsigned char** data=0,
				  int* filter=0,
				  int* internalFormats=0,
				  int* formats=0,
				  bool clamp=false,
				  int* attachments=0);

	virtual ~imageResource();

	void initTextures(unsigned char** data,
					  int* filter,
					  int* internalFormats,
					  int* formats,
					  bool clamp);
	void initRenderTargets(int* attachments);

	int getTarget() const { return m_target; }

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	void use(int ind);
	void useAsRenderTarget();

	void addReference();
	bool removeReference();
	
	int getID();

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<imageResource>("imageResource")
			.addFunction("getWidth", &imageResource::getWidth)
			.addFunction("getHeight", &imageResource::getHeight)
			.addFunction("getTarget", &imageResource::getTarget)
			.addFunction("use", &imageResource::use)
			.addFunction("useAsRenderTarget", &imageResource::useAsRenderTarget)
			.addFunction("addReference", &imageResource::addReference)
			.addFunction("removeReference", &imageResource::removeReference)
			.addFunction("getID", &imageResource::getID)
			.endClass();
	}
private:
	int* m_id;
	int m_fbo;
	int m_numTextures;
	int m_refCount;
	int m_target;
	
	int m_width, m_height;
	
	int* genTextures(int count);

	imageResource(imageResource& other) {}
	void operator=(imageResource& other) {}
};

#endif //__IX_IMG_RES__