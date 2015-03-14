#ifndef __IX_SCREEN__
#define __IX_SCREEN__
#pragma once

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
	static color* drawcolor;
	static bool quit;
	static screen* win;
	static SDL_Event evt;
	static Matrix4 projection;
	static bool lighting_enabled;

	static std::map<std::string, boxoccluder*> occluders;
	static std::map<std::string, light*> lights;

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
	static image* load_image(std::string filename);
	static image* create_image(int w, int h);
	static point* image_size(image* img);
	static void start_rendertexture(image* target);
	static void end_rendertexture();
	static void free_image(image* img);
	static void set_image_cliprect(image* img, int x, int y, int w, int h);
	static animation* sprite_animation(image* sheet, int rows, int cols, float speed, bool loop);
	static void console_visible(bool state);
	static void set_icon(const char* icon);
	static void is_lighting_enabled(bool en) { lighting_enabled = en; }
	static void add_light(std::string name, light* l);
	static void add_occluder(std::string name, boxoccluder* o);
	static void remove_light(std::string name);
	static void remove_occluder(std::string name);

	// Audio
	static audio* load_audio(std::string filename);
	static void set_audio_volume(audio* au, float volume);
	static void set_audio_pitch(audio* au, float pitch);
	static void set_audio_pan(audio* au, float pan);
	static void set_audio_loop(audio* au, bool loop);
	static void set_audio_play_once(audio* au, bool po);
	static void set_audio_properties(audio* au, float vol, float pitch, float pan, bool loop, bool playonce);
	
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
			.addFunction("addlight", &screen_mgr::add_light)
			.addFunction("addoccluder", &screen_mgr::add_occluder)
			.addFunction("removelight", &screen_mgr::remove_light)
			.addFunction("removeoccluder", &screen_mgr::remove_occluder)
			.addFunction("lighting", &screen_mgr::is_lighting_enabled)
			.addFunction("loadaudio", &screen_mgr::load_audio)
			.addFunction("setaudiovolume", &screen_mgr::set_audio_volume)
			.addFunction("setaudiopitch", &screen_mgr::set_audio_pitch)
			.addFunction("setaudiopan", &screen_mgr::set_audio_pan)
			.addFunction("setaudioloop", &screen_mgr::set_audio_loop)
			.addFunction("setaudioplayonce", &screen_mgr::set_audio_play_once)
			.addFunction("setaudioproperties", &screen_mgr::set_audio_properties)
			.addFunction("spriteanimation", &screen_mgr::sprite_animation)
			.addFunction("screen", &screen_mgr::init)
			.addFunction("cls", &screen_mgr::cls)
			.addFunction("flip", &screen_mgr::flip)
			.addFunction("poll", &screen_mgr::poll)
			.addFunction("keystatus", &screen_mgr::keystatus)
			.addFunction("getkey", &screen_mgr::getkey)
			.addFunction("startimagerender", &screen_mgr::start_rendertexture)
			.addFunction("endimagerender", &screen_mgr::end_rendertexture)
			.addFunction("freeimage", &screen_mgr::free_image)
			.addFunction("setimagecliprect", &screen_mgr::set_image_cliprect)
			.addFunction("mousex", &screen_mgr::mousex)
			.addFunction("mousey", &screen_mgr::mousey)
			.addFunction("getbutton", &screen_mgr::getbutton)
			.addFunction("buttonstatus", &screen_mgr::buttonstatus)
			.addFunction("color", &screen_mgr::set_draw_color)
			.addFunction("backcolor", &screen_mgr::set_back_color)
			.addFunction("resizewindow", &screen_mgr::resizewindow)
			.addFunction("windowsize", &screen_mgr::windowsize)
			.addFunction("setwindowtitle", &screen_mgr::settitle)
			.addFunction("loadimage", &screen_mgr::load_image)
			.addFunction("createimage", &screen_mgr::create_image)
			.addFunction("imagesize", &screen_mgr::image_size)
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
	static shader* lighting;
	static void ortho_2d(float* mat, int left, int top, int bottom, int right);
};

#endif //__IX_SCREEN__