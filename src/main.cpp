
#include "../include/GameWindow.h"
#include "../include/Text.h"
#include "../include/simplemove.h"
#include "../include/light.h"
#include "../include/assetpackage.h"

Sprite* spr;
Text* tex;
GameWindow* win;
Light* light1, *light2;
Node* light_node, *light_node2;
Script* mousemove;
AssetPackage* pak;

void init()
{    
    pak = new AssetPackage("exp.zip");

    light1 = new Light();
    light1->setIntensity(30.0f);
    light1->setColor(1.0f, 0.4f, 0.2f);

    light2 = new Light();
    light2->setIntensity(30.0f);
    light2->setColor(0.3f, 0.4f, 1.0f);

    light_node = new Node();
    light_node->setName("Light1");
    light_node->getTransform()->setTranslation(Vector3(200.0f, 200.0f, 40.0f));
    light_node->addComponent("Light_comp1", light1);

    light_node2 = new Node();
    light_node2->setName("Light2");
    light_node2->getTransform()->setTranslation(Vector3(400.0f, 200.0f, 40.0f));
    light_node2->addComponent("Light_comp2", light2);

    mousemove = pak->loadScript("move.lua", win->getLuaEngine());
    light_node2->attachScript(mousemove);

    spr = new Sprite(pak->loadTexture("bolt/bolt.png"), pak->loadTexture("bolt/boltn.png"));
    spr->setName("spr");
    spr->getTransform()->setTranslation(Vector3(250.0f, 250.0f, 0.0f));
    spr->addComponent("simplemovecomp", new SimpleMove());

    spr->getMaterial()->getDiffuseTexture()->setFilter(GL_LINEAR);
    spr->getMaterial()->getNormalTexture()->setFilter(GL_LINEAR);
    spr->getMaterial()->setSpecularPower(12.0f);

    tex = new Text(pak->loadFont("dfont.ttf"));
    tex->setName("label");
    tex->setText("DQBIX Game Engine: Lighting & Normal Map Test\nUse [ARROW-KEYS] to move the bolt.\nUse [W] and [S] to increase/decrease the light intensity.");
    tex->setColor(1.0f, 1.0f, 1.0f, 1.0f);
    tex->getTransform()->setTranslation(Vector3(20, 28, 0));
    tex->getTransform()->setScale(Vector3(1.0f, -1.0f, 1.0f));

    win->getTree()->addChild(spr);
    win->getTree()->addChild(tex);
    win->getTree()->addChild(light_node);
    win->getTree()->addChild(light_node2);

}

int main(int argc, char** argv)
{
    win = new GameWindow();
    win->createWindow(640, 480, "Test");
    Color amb(0.2, 0.2, 0.2, 1.0);
    win->setAmbient(amb);

    win->init = init;

    win->mainloop();

    SAFE_DELETE(win);
    pak->DisposeTempFiles();

    return 0;
}
