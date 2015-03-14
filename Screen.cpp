#include "Screen.h"

screen* screen_mgr::win = NULL;
SDL_Event screen_mgr::evt;
Matrix4 screen_mgr::projection;

bool screen_mgr::lighting_enabled;
bool screen_mgr::quit = false;

std::map<std::string, boxoccluder*> screen_mgr::occluders;
std::map<std::string, light*> screen_mgr::lights;

color* screen_mgr::drawcolor = NULL;
shader* screen_mgr::lighting;

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

void screen_mgr::add_light(std::string name, light* l)
{
	lights[name] = l;
}

void screen_mgr::add_occluder(std::string name, boxoccluder* o)
{
	occluders[name] = o;
}

void screen_mgr::remove_light(std::string name)
{
	std::map<std::string, light*>::const_iterator pos = lights.find(name);
	if (pos != lights.cend())
	{
		lights.erase(name);
	}
}

void screen_mgr::remove_occluder(std::string name)
{
	std::map<std::string, boxoccluder*>::const_iterator pos = occluders.find(name);
	if (pos != occluders.cend())
	{
		occluders.erase(name);
	}
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

	glClearColor(win->backcolor->r, win->backcolor->g, win->backcolor->b, win->backcolor->a);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (lighting_enabled)
	{
		glClearStencil(0);
		for (auto &rlight : lights)
		{
			light* light = rlight.second;
			if (light->getIntensity() <= 0.0f) continue;

			if (light->getCastshadow())
			{
				glClearStencil(0);
				glClear(GL_STENCIL_BUFFER_BIT);

				glEnable(GL_STENCIL_TEST);
				glStencilFunc(GL_ALWAYS, 0x1, 0x1);
				glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
				glColorMask(false, false, false, false);

				glColor4f(1, 1, 1, 0.7f);

				for (auto &roccluder : occluders)
				{
					boxoccluder* occluder = roccluder.second;
					int count = 4;
					Vector2 verts[4] = {
						Vector2(occluder->getX(), occluder->getY()),
						Vector2(occluder->getX() + occluder->getW(), occluder->getY()),
						Vector2(occluder->getX() + occluder->getW(), occluder->getY() + occluder->getH()),
						Vector2(occluder->getX(), occluder->getY() + occluder->getH()),
					};
					for (int i = 0; i < count; i++)
					{
						Vector2 current = verts[i];
						Vector2 next = verts[(i + 1) % count];
						Vector2 edge = next - current;
						Vector2 normal = Vector2(edge.y, -edge.x);
						Vector2 lightPos = Vector2(light->getX(), light->getY());
						Vector2 lightToCurrent = current - lightPos;
						if (normal.dot(lightToCurrent) > 0)
						{
							Vector2 point1 = (current + (lightToCurrent)* 800);
							Vector2 point2 = (next + (next - lightPos) * 800);

							glBegin(GL_QUADS);
							glVertex2f(current.x, current.y);
							glVertex2f(point1.x, point1.y);
							glVertex2f(point2.x, point2.y);
							glVertex2f(next.x, next.y);
							glEnd();
						}
					}
				}
				glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
				glStencilFunc(GL_EQUAL, 0x0, 0x1);
				glColorMask(true, true, true, true);
			}
			
			lighting->use();
			lighting->setVec2("lightPos", light->getX(), win->h - light->getY());
			lighting->setVec3("lightColor", light->getColor()->r,
				light->getColor()->g,
				light->getColor()->b);
			lighting->setFloat("intensity", light->getIntensity());
			lighting->setFloat("radius", light->getRadius());

			glBlendFunc(GL_ONE, GL_ONE);

			glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f(0, win->h);
			glVertex2f(win->w, win->h);
			glVertex2f(win->w, 0);
			glEnd();

			glBlendFunc(GL_DST_COLOR, GL_ONE);
			glUseProgram(0);			
		}
	}
}

void screen_mgr::flip()
{
	if (!quit)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		SDL_GL_SwapBuffers();
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
	projection.set(m);

	glViewport(0, 0, wn->w, wn->h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projection.get());

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

	std::string frag = "#version 120\n"
		"uniform vec2 lightPos;"
		"uniform vec3 lightColor;"
		"uniform float intensity;"
		"uniform float radius;"
		"void main()"
		"{"
		"	float distance = length(lightPos - gl_FragCoord.xy);"
		"	float attenuation = 1.0 / ((1.0+10.0/((radius+50.0)/distance)));"
		"	vec4 color = intensity * vec4(attenuation, attenuation, attenuation, 1);"
		"	gl_FragColor = color * vec4(lightColor, 1.0);"
		"}";
	
	lighting = new shader();
	lighting->fromString("", frag);

	lighting->addUniform("lightPos");
	lighting->addUniform("lightColor");
	lighting->addUniform("intensity");
	lighting->addUniform("radius");
}