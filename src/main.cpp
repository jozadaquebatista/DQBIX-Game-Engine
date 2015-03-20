
#include "../include/GameWindow.h"
#include "../include/Sprite.h"
#include "../include/AnimatedSprite.h"

Sprite* spr;
Sprite* spd;
AnimatedSprite* anim;

void init()
{
	anim = new AnimatedSprite(new Texture("exp.png"), 4, 5, 0.04f, true);
	anim->getTransform()->move(200.0f, 200.0f, 0.0f);
	anim->getTransform()->setScale(vec3(0.12f, 0.12f, 0.12f));

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
	anim->step();
}

void render()
{
	spr->drawAll();
	anim->drawAll();
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