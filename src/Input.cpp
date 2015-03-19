#include "..\include\Input.h"

SDL_Event Input::evt;

int Input::mX = 0;
int Input::mY = 0;

bool Input::inputs[NUMKEYS];
bool Input::downKeys[NUMKEYS];
bool Input::upKeys[NUMKEYS];

bool Input::mouseInputs[NUMMOUSEBUTTONS];
bool Input::downMouse[NUMMOUSEBUTTONS];
bool Input::upMouse[NUMMOUSEBUTTONS];

void Input::update()
{
	for (int i = 0; i < NUMMOUSEBUTTONS; i++)
	{
		downMouse[i] = false;
		upMouse[i] = false;
	}

	for (int i = 0; i < NUMKEYS; i++)
	{
		downKeys[i] = false;
		upKeys[i] = false;
	}

	while (SDL_PollEvent(&evt))
	{

		if (evt.type == SDL_MOUSEMOTION)
		{
			mX = evt.motion.x;
			mY = evt.motion.y;
		}

		if (evt.type == SDL_KEYDOWN)
		{
			int value = evt.key.keysym.sym;

			inputs[value] = true;
			downKeys[value] = true;
		}
		if (evt.type == SDL_KEYUP)
		{
			int value = evt.key.keysym.sym;

			inputs[value] = false;
			upKeys[value] = true;
		}
		if (evt.type == SDL_MOUSEBUTTONDOWN)
		{
			int value = evt.button.button;

			mouseInputs[value] = true;
			downMouse[value] = true;
		}
		if (evt.type == SDL_MOUSEBUTTONUP)
		{
			int value = evt.button.button;

			mouseInputs[value] = false;
			upMouse[value] = true;
		}
	}
}

bool Input::getKey(int keycode)
{
	return inputs[keycode];
}

bool Input::getKeyDown(int keycode)
{
	return downKeys[keycode];
}

bool Input::getKeyUp(int keycode)
{
	return upKeys[keycode];
}

bool Input::getMouse(int btncode)
{
	return mouseInputs[btncode];
}

bool Input::getMouseDown(int btncode)
{
	return downMouse[btncode];
}

bool Input::getMouseUp(int btncode)
{
	return upMouse[btncode];
}

glm::vec2 Input::getMousePosition()
{
	return vec2((float)mX, (float)mY);
}

void Input::setMousePosition(vec2 p)
{
	SDL_WarpMouse((float)p.x, (float)p.y);
}

void Input::setCursor(bool cur)
{
	SDL_ShowCursor(cur ? 1 : 0);
}
