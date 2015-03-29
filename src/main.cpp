
#include "../include/GameWindow.h"
#include "../include/Text.h"
#include "../include/simplemove.h"
#include "../include/light.h"

Sprite* spr;
AnimatedSprite* anim;
Text* tex;
GameWindow* win;
Light* light1, *light2;
Node* light_node, *light_node2;

void init()
{    
    light1 = new Light();
    light1->setIntensity(1000.0f);
    light1->setColor(1.0f, 0.7f, 0.3f);

    light2 = new Light();
    light2->setIntensity(1000.0f);
    light2->setColor(0.2f, 0.3f, 0.7f);

    light_node = new Node();
    light_node->setName("Light1");
    light_node->getTransform()->setTranslation(Vector3(200.0f, 200.0f, 40.0f));
    light_node->addComponent(light1);

    light_node2 = new Node();
    light_node2->setName("Light2");
    light_node2->getTransform()->setTranslation(Vector3(300.0f, 200.0f, 40.0f));
    light_node2->addComponent(light2);

    anim = new AnimatedSprite(new Texture("exp.png"), 4, 5, 0.04f, true);
    anim->setName("anim");
    anim->getTransform()->move(200.0f, 200.0f, 0.0f);
    anim->getTransform()->setScale(Vector3(0.2f, 0.2f, 1.0f));

    spr = new Sprite("data/monkey_d.png", "data/monkey_n.png");
    spr->setName("spr");
    spr->getTransform()->setTranslation(Vector3(250.0f, 250.0f, 0.0f));
    spr->addComponent(new SimpleMove());

    spr->getMaterial()->setSpecularPower(1.0f);
    spr->getMaterial()->setSpecularHardness(5.0f);

    tex = new Text("dfont.ttf", 18);
    tex->setName("label");
    tex->setText("DQBIX Game Engine Test");
    tex->setColor(1.0f, 1.0f, 1.0f, 1.0f);
    tex->getTransform()->setTranslation(Vector3(28, 28, 0));
    tex->getTransform()->setScale(Vector3(1.0f, -1.0f, 1.0f));

    win->getTree()->addChild(anim);
    win->getTree()->addChild(spr);
    win->getTree()->addChild(tex);
    win->getTree()->addChild(light_node);
    win->getTree()->addChild(light_node2);
}

int main(int argc, char** argv)
{
    win = new GameWindow();
    win->createWindow(640, 480, "Test");
    Color amb;
    amb.r = amb.g = amb.b = 0.1;
    amb.a = 1.0f;
    win->setAmbient(amb);

    win->init = init;

    win->mainloop();
    SAFE_DELETE(win);
    return 0;
}
