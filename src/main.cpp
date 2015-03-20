
#include "../include/GameWindow.h"
#include "../include/Sprite.h"

Sprite* spr;
Sprite* spd;

void init()
{
	spr = new Sprite("data/monkey_n.png");
	spr->getTransform()->setTranslation(vec3(250.0f, 250.0f, 0.0f));
	spr->getTransform()->rotate_transform(0.0f, 0.0f, 45.0f);

	spd = new Sprite("data/monkey_d.png");
	spd->getTransform()->setTranslation(vec3(128.0f, 0.0f, 0.0f));
	spr->addChild(spd);
}

void update(float d)
{
	spr->getTransform()->rotate_transform(0.0f, 0.0f, 0.025f);
}

void render()
{
	spr->drawAll();
}

int main(int argc, char* argv[])
{
	GameWindow* win = new GameWindow();
	win->createWindow(640, 480, "Test");

	win->init = init;
	win->render = render;
	win->update = update;

	win->mainloop();
	return 0;
}