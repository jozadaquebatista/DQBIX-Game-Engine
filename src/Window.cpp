#include "..\include\Window.h"

static bool quit = false;

void Window::createWindow(int width, int height, std::string title)
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
}

void Window::render()
{
	if (!quit)
		SDL_GL_SwapBuffers();
}

bool Window::closed()
{
	if (Input::evt.type == SDL_QUIT)
	{
		quit = true;
		return true;
	}
	return false;
}

int Window::getWidth()
{
	const SDL_VideoInfo* info;
	info = SDL_GetVideoInfo();
	return info->current_w;
}
int Window::getHeight()
{
	const SDL_VideoInfo* info;
	info = SDL_GetVideoInfo();
	return info->current_h;
}

float Window::getAspect()
{
	return (float)getWidth() / (float)getHeight();
}

std::string Window::getTitle()
{
	char* title;
	SDL_WM_GetCaption(&title, NULL);
	return std::string(title);
}
