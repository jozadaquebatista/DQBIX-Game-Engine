#include "..\include\GameWindow.h"

static float FRAME_CAP = 60.0f;
static bool quit = false;
static bool running = false;

mat4 GameWindow::Projection;

void GameWindow::ortho_2d(float* mat, int left, int right, int bottom, int top)
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

void GameWindow::mainloop()
{
	running = true;

	const float frameTime = 1.0f / (float)FRAME_CAP;

	int lastTime = Time::getTime();
	float unprocessedTime = 0.0f;

	int frames = 0;
	int frameCounter = 0;

	if (init) init();

	while (running)
	{
		bool can_render = false;

		int startTime = Time::getTime();
		int passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime += (float)passedTime / (float)Time::SECOND;
		frameCounter += passedTime;

		while (unprocessedTime > frameTime)
		{
			can_render = true;

			unprocessedTime -= frameTime;

			Time::setDelta(frameTime);
			Input::update();

			if (GameWindow::closed())
				running = false;

			m_tree->update(frameTime);

			if (frameCounter >= Time::SECOND)
			{
				frames = 0;
				frameCounter = 0;
			}
		}

		if (can_render)
		{
			RenderUtil::clearScreen();
			m_tree->render();

			if (!quit)
				SDL_GL_SwapBuffers();
			frames++;
		}
		else
			SDL_Delay(1);
	}
	SAFE_DELETE(eng);
	SDL_Quit();
}

void GameWindow::createWindow(int width, int height, std::string title)
{
	//// Recycled code from Screen.cpp ////
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "Window creation error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption(title.c_str(), NULL);

	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create a Video Mode as an OpenGL context
	if (SDL_SetVideoMode(width, height, 32, SDL_OPENGL) == 0)
	{
		fprintf(stderr, "Set Video Mode error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	// Init GLEW
	glewExperimental = TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("OpenGL Extensions initialization failed.");
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	float mat[16];
	ortho_2d(mat, 0, width, height, 0);
	Projection = make_mat4(mat);

	RenderUtil::initGraphics(GameWindow::getWidth(), GameWindow::getHeight());

	m_tree = new SceneTree();

	running = true;

	// Register Lua Objects
	eng = new LuaEngine();
	point::lua_reg(eng->getState());
	Node::RegisterObject(eng->getState());
	Texture::RegisterObject(eng->getState());
	Transform::RegisterObject(eng->getState());
	Sprite::RegisterObject(eng->getState());
	AnimatedSprite::RegisterObject(eng->getState());
	Input::RegisterObject(eng->getState());
}

bool GameWindow::closed()
{
	if (Input::evt.type == SDL_QUIT)
	{
		running = false;
		quit = true;
		return true;
	}
	return false;
}

int GameWindow::getWidth()
{
	const SDL_VideoInfo* info;
	info = SDL_GetVideoInfo();
	return info->current_w;
}
int GameWindow::getHeight()
{
	const SDL_VideoInfo* info;
	info = SDL_GetVideoInfo();
	return info->current_h;
}

float GameWindow::getAspect()
{
	return (float)getWidth() / (float)getHeight();
}

std::string GameWindow::getTitle()
{
	char* title;
	SDL_WM_GetCaption(&title, NULL);
	return std::string(title);
}
