#ifndef __IX_RENDERER__
#define __IX_RENDERER__
#pragma once

#include "../include/Screen.h"
#include "../include/font.h"
#include "../include/shader.h"
#include <iostream>

class renderer
{
public:
	static void blit_full(Texture* img, int x, int y, float sx, float sy, float a);
	static void blits(Texture* img, int x, int y, float sx, float sy);
	static void blitr(Texture* img, int x, int y, float a);
	static void blit(Texture* img, int x, int y);

	static void drawtext(std::string text, int x, int y, font* fnt);
	static void drawtextr(std::string text, int x, int y, float a, font* fnt);
	
	static void line(int x1, int y1, int x2, int y2);
	static void dot(int x, int y);
	static void circle(int x, int y, int r, bool fill = false);
	static void rect(int x, int y, int w, int h, bool fill = false);

	static void lua_reg(lua_State* L);
	
};

#endif //__IX_RENDERER__