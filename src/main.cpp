
#include "../include/GameWindow.h"
#include "../include/Text.h"
#include "../include/simplemove.h"

Sprite* spr;
AnimatedSprite* anim;
Text* tex;
GameWindow* win;

void init()
{    
    anim = new AnimatedSprite(new Texture("exp.png"), 4, 5, 0.04f, true);
    anim->setName("anim");
    anim->getTransform()->move(200.0f, 200.0f, 0.0f);
    anim->getTransform()->setScale(Vector3(0.2f, 0.2f, 1.0f));

    spr = new Sprite("data/monkey_n.png");
    spr->setName("spr");
    spr->getTransform()->setTranslation(Vector3(250.0f, 250.0f, 0.0f));
    spr->addComponent(new SimpleMove());

    tex = new Text("../res/dfont.ttf", 18);
    tex->setName("label");
    tex->setText("DQBIX Game Engine Test");
    tex->setColor(1.0f, 1.0f, 1.0f, 1.0f);
    tex->getTransform()->setTranslation(Vector3(28, 28, 0));
    tex->getTransform()->setScale(Vector3(1.0f, -1.0f, 1.0f));

    win->getTree()->addChild(anim);
    win->getTree()->addChild(spr);
    win->getTree()->addChild(tex);
}

int main(int argc, char** argv)
{
    win = new GameWindow();
    win->createWindow(640, 480, "Test");

    win->init = init;

    win->mainloop();
    SAFE_DELETE(win);
    return 0;
}
