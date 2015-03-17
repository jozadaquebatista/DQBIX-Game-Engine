#ifndef __IX_SCREEN__
#define __IX_SCREEN__
#pragma once

#ifndef MAX_FRAMERATE
#define MAX_FRAMERATE 60
#endif

#include "sdl_backend.h"
#include "font.h"
#include "collisiondetection.h"
#include "animation.h"
#include "audio.h"
#include "shader.h"

#include "occluder.h"
#include "light.h"

typedef struct
{
	int w, h, bpp, flags;
	const SDL_VideoInfo* info;
	color* backcolor;
} screen;

class screen_mgr
{
public:
	static mat4 projection;

	static color* drawcolor;
	static bool quit;
	static screen* win;
	static SDL_Event evt;	

	static void init(int w, int h, int bpp, const char* title);
	static void cls();
	static void flip();
	static void poll();
	static void opengl_setup(screen* wn);

	static bool keystatus(int key);
	static int getkey();

	static int mousex();
	static int mousey();
	static int getbutton();
	static bool buttonstatus(int btn);

	static void resizewindow(int nw, int nh);
	static point* windowsize();
	static void settitle(std::string newtitle);

	static void quit_game();

	static void set_draw_color(float r, float g, float b, float a);
	static void set_back_color(float r, float g, float b, float a);

	// Lua functions
	static void start_rendertexture(image* target);
	static void end_rendertexture();
	static void free_image(image* img);
	static void console_visible(bool state);
	static void set_icon(const char* icon);

	static image* create_rendertarget(int w, int h);

	static void useAsRenderTarget();

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<color>("colors")
			.addData("r", &color::r)
			.addData("g", &color::g)
			.addData("b", &color::b)
			.addData("a", &color::a)
			.endClass()
			.addFunction("createtarget", &screen_mgr::create_rendertarget)
			.addFunction("screen", &screen_mgr::init)
			.addFunction("cls", &screen_mgr::cls)
			.addFunction("flip", &screen_mgr::flip)
			.addFunction("poll", &screen_mgr::poll)
			.addFunction("keystatus", &screen_mgr::keystatus)
			.addFunction("getkey", &screen_mgr::getkey)
			.addFunction("startimagerender", &screen_mgr::start_rendertexture)
			.addFunction("endimagerender", &screen_mgr::end_rendertexture)
			.addFunction("freeimage", &screen_mgr::free_image)
			.addFunction("mousex", &screen_mgr::mousex)
			.addFunction("mousey", &screen_mgr::mousey)
			.addFunction("getbutton", &screen_mgr::getbutton)
			.addFunction("buttonstatus", &screen_mgr::buttonstatus)
			.addFunction("color", &screen_mgr::set_draw_color)
			.addFunction("backcolor", &screen_mgr::set_back_color)
			.addFunction("resizewindow", &screen_mgr::resizewindow)
			.addFunction("windowsize", &screen_mgr::windowsize)
			.addFunction("setwindowtitle", &screen_mgr::settitle)
			.addFunction("quit", &screen_mgr::quit_game)
			.addFunction("seticon", &screen_mgr::set_icon)
			.addFunction("consolevisible", &screen_mgr::console_visible);
			
		point::lua_reg(L);
		image::lua_reg(L);
		animation::lua_reg(L);
		audio::lua_reg(L);
		collisiondetection::lua_reg(L);
		font::lua_reg(L);
		light::lua_reg(L);
		boxoccluder::lua_reg(L);
	}
private:
	static int frame;
	static bool cap;
	static int ticks, lastticks;
	static void ortho_2d(float* mat, int left, int top, int bottom, int right);
	
};

#endif //__IX_SCREEN__