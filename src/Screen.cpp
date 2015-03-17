#include "../include/Screen.h"

mat4 screen_mgr::projection;

void screen_mgr::ortho_2d(float* mat, int left, int right, int bottom, int top)
{
	const float zNear = -1.0f;
	const float zFar = 1.0f;
	const float inv_z = 1.0f / (zFar - zNear);
	const float inv_y = 1.0f / (top - bottom);
	const float inv_x = 1.0f / (right - left);

	//first column
	*mat++ = (2.0f*inv_x);
	*mat++ = (0.0f);
	*mat++ = (0.0f);
	*mat++ = (0.0f);

	//second
	*mat++ = (0.0f);
	*mat++ = (2.0f*inv_y);
	*mat++ = (0.0f);
	*mat++ = (0.0f);

	//third
	*mat++ = (0.0f);
	*mat++ = (0.0f);
	*mat++ = (-2.0f*inv_z);
	*mat++ = (0.0f);

	//fourth
	*mat++ = (-(right + left)*inv_x);
	*mat++ = (-(top + bottom)*inv_y);
	*mat++ = (-(zFar + zNear)*inv_z);
	*mat++ = (1.0f);
}

screen* screen_mgr::win = NULL;
SDL_Event screen_mgr::evt;
bool screen_mgr::quit = false;

color* screen_mgr::drawcolor = NULL;

int screen_mgr::frame = 0;
bool screen_mgr::cap = true;

int screen_mgr::lastticks;
int screen_mgr::ticks;

std::map<std::string, light*> screen_mgr::lights;
shader* screen_mgr::m_shader;

int screen_mgr::getkey()
{
	if (&evt == NULL) return -1;
	if (evt.type == SDL_KEYDOWN)
	{
		return (int)evt.key.keysym.sym;
	}
	return -1;
}

bool screen_mgr::keystatus(int key)
{
	Uint8* state = SDL_GetKeyState(0);
	return state[key] == 1;
}

int screen_mgr::mousex()
{
	int x;
	SDL_PumpEvents();
	SDL_GetMouseState(&x, NULL);
	return x;
	/*if (&evt == NULL) return -1;
	if (evt.type == SDL_MOUSEMOTION)
	{
		return evt.motion.x;
	}
	return -1;*/
}

int screen_mgr::mousey()
{
	int y;
	SDL_PumpEvents();
	SDL_GetMouseState(NULL, &y);
	return y;
	/*if (&evt == NULL) return -1;
	if (evt.type == SDL_MOUSEMOTION)
	{
	return evt.motion.y;
	}
	return -1;*/
}

int screen_mgr::getbutton()
{
	SDL_PumpEvents();
	return SDL_GetMouseState(NULL, NULL);
	// Old code
	/*if (&evt == NULL) return -1;
	if (evt.type == SDL_MOUSEMOTION || evt.type == SDL_MOUSEBUTTONDOWN)
	{
		return evt.motion.state;
	}*/
	//return -1;
}

bool screen_mgr::buttonstatus(int btn)
{
	return getbutton() == btn;
}

void screen_mgr::resizewindow(int nw, int nh)
{
	win->w = nw;
	win->h = nh;
	SDL_SetVideoMode(win->w, win->h, win->bpp, win->flags);
	opengl_setup(win);
}

point* screen_mgr::windowsize()
{
	return new point((float)win->w, (float)win->h);
}


void screen_mgr::settitle(std::string newtitle)
{
	SDL_WM_SetCaption(newtitle.c_str(), NULL);
}

void screen_mgr::start_rendertexture(image* target)
{
	target->setAsRenderTarget();
}

void screen_mgr::end_rendertexture()
{
	useAsRenderTarget();
}

void screen_mgr::free_image(image* img)
{
	if (img) delete img;
	img = NULL;
}

void screen_mgr::useAsRenderTarget()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, win->w, win->h);
}

void screen_mgr::console_visible(bool state)
{
	if (!state)
	{
		FreeConsole();
	}
	else
	{
		AllocConsole();
	}
}

void screen_mgr::set_icon(const char* icon)
{
	SDL_WM_SetIcon(image::loadicon(icon), NULL);
}

image* screen_mgr::create_rendertarget(int w, int h)
{
	return new image(w, h, 0, GL_TEXTURE_2D, GL_NEAREST, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0);
}

void screen_mgr::quit_game()
{
	quit = true;
	SDL_Quit();
	BASS_Free();
	exit(EXIT_SUCCESS);
}

void screen_mgr::set_draw_color(float r, float g, float b, float a)
{
	drawcolor = new color();
	drawcolor->r = r;
	drawcolor->g = g;
	drawcolor->b = b;
	drawcolor->a = a;
}

void screen_mgr::set_back_color(float r, float g, float b, float a)
{
	win->backcolor = new color();
	win->backcolor->r = r;
	win->backcolor->g = g;
	win->backcolor->b = b;
	win->backcolor->a = a;
}

void screen_mgr::cls()
{
	if (drawcolor == NULL)
	{
		drawcolor = new color();
		drawcolor->r = 1.0f;
		drawcolor->g = 1.0f;
		drawcolor->b = 1.0f;
		drawcolor->a = 1.0f;
	}

	ticks = SDL_GetTicks();

	glClearColor(win->backcolor->r, win->backcolor->g, win->backcolor->b, win->backcolor->a);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void screen_mgr::flip()
{
	if (!quit)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		SDL_GL_SwapBuffers();
		
		if ((ticks - lastticks) < 1000 / MAX_FRAMERATE)
			SDL_Delay(1000 / MAX_FRAMERATE - (ticks - lastticks));
		lastticks = ticks;
	}
}

void screen_mgr::poll()
{
	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			quit_game();
			break;
		}
	}
}

void screen_mgr::opengl_setup(screen* wn)
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_STENCIL_TEST);

	glFrontFace(GL_CCW);

	if (wn->backcolor == NULL)
	{
		wn->backcolor = new color();
		wn->backcolor->r = 0;
		wn->backcolor->g = 0;
		wn->backcolor->b = 0;
		wn->backcolor->a = 0;
	}
	float m[16];
	ortho_2d(m, 0, wn->w, wn->h, 0);
	projection = make_mat4(m);

	glViewport(0, 0, wn->w, wn->h);

	useAsRenderTarget();
}

void screen_mgr::init(int w, int h, int bpp, const char* title)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	win = new screen();
	win->info = SDL_GetVideoInfo();

	if (!win->info)
	{
		fprintf(stderr, "error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	win->w = w;
	win->h = h;
	win->bpp = bpp <= -1 ? win->info->vfmt->BitsPerPixel : bpp;

	SDL_WM_SetCaption(title, NULL);

	// Set GL attributes
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	win->flags = SDL_OPENGL;

	if (SDL_SetVideoMode(win->w, win->h, win->bpp, win->flags) == 0)
	{
		fprintf(stderr, "error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	glewExperimental = TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW init failed.");
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	opengl_setup(win);

	if (!BASS_Init(-1, 44100, 0, NULL, NULL))
	{
		printf("Audio Error\n");
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	//m_shader = new shader();
	//m_shader->fromString(/*TODO*/default_vert, shaded_frag);

	//m_shader->compile();
	//m_shader->addCommonUniforms();
	//m_shader->addUniform("diffuse");
	//m_shader->addUniform("normal");
	//m_shader->addUniform("cliprect");
	//m_shader->addUniform("Resolution");
	//m_shader->addUniform("LightPos");
	//m_shader->addUniform("LightColor");
	//m_shader->addUniform("AmbientColor");
	//m_shader->addUniform("Falloff");
}
