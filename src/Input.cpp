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

point Input::getMousePosition()
{
	return point((float)mX, (float)mY);
}

void Input::setMousePosition(float x, float y)
{
	SDL_WarpMouse((int)x, (int)y);
}

void Input::setCursor(bool cur)
{
	SDL_ShowCursor(cur ? 1 : 0);
}

void Input::RegisterObject(lua_State* L)
{
	using namespace luabridge;

	getGlobalNamespace(L)
		.beginClass<Input>("Input")
			.addStaticFunction("getKey", &Input::getKey)
			.addStaticFunction("getKeyDown", &Input::getKeyDown)
			.addStaticFunction("getKeyUp", &Input::getKeyUp)
			.addStaticFunction("getMouse", &Input::getMouse)
			.addStaticFunction("getMouseDown", &Input::getMouseDown)
			.addStaticFunction("getMouseUp", &Input::getMouseUp)
			.addStaticFunction("getMousePosition", &Input::getMousePosition)
			.addStaticFunction("setMousePosition", &Input::setMousePosition)
			.addStaticFunction("setCursor", &Input::setCursor)
		.endClass();
}
