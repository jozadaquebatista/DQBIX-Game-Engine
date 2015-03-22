
#include "../include/GameWindow.h"
#include "../include/Text.h"

Sprite* spr;
AnimatedSprite* anim;
Text* tex;
GameWindow* win;
Script *teste, *moves;

void init()
{
	teste = new Script("teste_script.lua", win->getLuaEngine());
	moves = new Script("move.lua", win->getLuaEngine());

	anim = new AnimatedSprite(new Texture("exp.png"), 4, 5, 0.04f, true);
	anim->setName("anim");
	anim->getTransform()->move(200.0f, 200.0f, 0.0f);
	anim->getTransform()->setScale(Vector3(0.5f, 0.5f, 0.5f));
	anim->attachScript(moves);

	spr = new Sprite("data/monkey_n.png");
	spr->setName("spr");
	spr->getTransform()->setTranslation(Vector3(250.0f, 250.0f, 0.0f));
	spr->getTransform()->rotate_transform(0.0f, 0.0f, 45.0f);
	spr->attachScript(teste);

	tex = new Text("andy.ttf", 32);
	tex->setText("Hello World!");
	tex->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	tex->getTransform()->setTranslation(Vector3(120, 120, 0));
	tex->getTransform()->setScale(Vector3(1.0f, -1.0f, 1.0f));

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