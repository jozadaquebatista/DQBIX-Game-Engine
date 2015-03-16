#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <streambuf>
#include <ios>
#include <cmath>

#define NO_LIGHTING
#include "../include/Screen.h"

#include "../include/renderer.h"
#include "../include/tileset.h"
#include "../include/LuaEngine.hpp"

#include <cstdio>

// #define DEBUG_SCRIPT
// #define TEST_PROGRAM

#define PI 3.141592658
class argv_range {
public:
	argv_range(int argc, const char * const argv[])
		: argc_(argc), argv_(argv)
	{
	}

	const char * const *begin() const { return argv_; }
	const char * const *end() const { return argv_ + argc_; }

private:
	const int argc_;
	const char * const *argv_;
};

bool ends_with(std::string const & value, std::string const & ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

long getFileSize(FILE *file)
{
	long lCurPos, lEndPos;
	lCurPos = ftell(file);
	fseek(file, 0, 2);
	lEndPos = ftell(file);
	fseek(file, lCurPos, 0);
	return lEndPos;
}
void LoadFileInResource(int name, int type, DWORD& size, const char*& data)
{
	HMODULE handle = ::GetModuleHandle(NULL);
	HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(name),
		MAKEINTRESOURCE(type));
	HGLOBAL rcData = ::LoadResource(handle, rc);
	size = ::SizeofResource(handle, rc);
	data = static_cast<const char*>(::LockResource(rcData));
}

bool isbind = false;

#ifdef TEST_PROGRAM
int main(int argc, char *argv[])
{
	screen_mgr::init(640, 480, 32, "Test");
	image* bg = new image("data/bg2.png");
	image* im = new image("data/player.png");
	im->setOrigin(0.5f, 0.5f);
	animation* anim = new animation(im, 1, 4, 0.08f, true);

	int key = 0;
	float a = 0.0f;
	while (key != 27)
	{
		screen_mgr::poll();
		screen_mgr::cls();
		key = screen_mgr::getkey();

		renderer::blit(bg, 0, 0);
		renderer::blits(anim->step(), 100, 100, -4.0, 4.0);

		screen_mgr::flip();
		a += 0.05f;
	}
	screen_mgr::quit_game();
	return 0;
}
#else
//////////////////////////////////////////////////////////////////////////
//  This is the real main =)
int main(int argc, char *argv[])
{
	std::string scr;
	std::stringstream scr_s;
	int spos = -1;

	if (argc == 1)
	{
		isbind = true;
	}
	else {
		isbind = false;
	}

	if (isbind)
	{
		FILE* file = fopen(argv[0], "rb");
		long size = getFileSize(file);
		char* data = new char[size];
		fread(data, size, 1, file);
		fclose(file);

		// Search script
		for (int i = size - 1; i >= 0; i--)
		{
			char c = data[i];

			if (c == '±')
			{
				spos = i;
				break;
			}
			else { continue; }
		}
		if (spos != -1)
		{
			// Get script
			for (int i = spos + 2; i < size; i++)
			{
				scr_s << data[i];
			}
		}

		scr = scr_s.str();

		delete[] data;
	}

	LuaEngine *eng = new LuaEngine();

	// Register lua functions
	screen_mgr::lua_reg(eng->getLuaState());
	tileset::lua_reg(eng->getLuaState());
	renderer::lua_reg(eng->getLuaState());

#ifndef DEBUG_SCRIPT
	if (!isbind)
	{
		std::string script_path(argv[1]);
		if (ends_with(script_path, ".lua"))
			eng->RunScript(script_path.c_str());
		else
		{
			SAFE_DELETE(eng);
			std::cerr << "Invalid file: " << script_path << std::endl;
			return -1;
		}
	}
	else
	{
		std::ofstream fl("C:/tmp_scr.tmp");
		fl << scr;
		fl.close();
		eng->RunScript("C:/tmp_scr.tmp");
	}
	remove("C:/tmp_scr.tmp");
#else
	std::string script_path("test.lua");
	eng->RunScript(script_path.c_str());
#endif

	SAFE_DELETE(eng);
	return 0;
}
#endif