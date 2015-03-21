
#include "../include/GameWindow.h"
#include "../include/Sprite.h"
#include "../include/AnimatedSprite.h"
#include "../include/Text.h"

Sprite* spr;
Sprite* spd;
AnimatedSprite* anim;
Text* tex;
GameWindow* win;

void init()
{
	anim = new AnimatedSprite(new Texture("exp.png"), 4, 5, 0.04f, true);
	anim->setName("anim");
	anim->getTransform()->move(200.0f, 200.0f, 0.0f);
	anim->getTransform()->setScale(vec3(0.2f, 0.2f, 0.2f));

	spr = new Sprite("data/monkey_n.png");
	spr->setName("spr");
	spr->getTransform()->setTranslation(vec3(250.0f, 250.0f, 0.0f));
	spr->getTransform()->rotate_transform(0.0f, 0.0f, 45.0f);

	spd = new Sprite("data/monkey_d.png");
	spd->setName("spd");
	spd->getTransform()->setTranslation(vec3(128.0f, 64.0f, 0.0f));
	spr->addChild(spd);

	tex = new Text("andy.ttf", 32);
	tex->setText("Hello World!");
	tex->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	tex->getTransform()->setTranslation(vec3(120, 120, 0));
	tex->getTransform()->setScale(vec3(1.0f, -1.0f, 1.0f));

	win->getTree()->addChild(anim);
	win->getTree()->addChild(spr);
	win->getTree()->addChild(tex);
}

int main(int argc, char* argv[])
{
	win = new GameWindow();
	win->createWindow(640, 480, "Test");

	win->init = init;

	win->mainloop();
	return 0;
}