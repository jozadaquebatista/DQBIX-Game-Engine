#include "../include/GameWindow.h"
#include "../include/Text.h"

// Vars ///////
GameWindow* win;
Sprite* test;
Node* lnode;
Light* light;

void init()
{
    lnode = win->createNode();
    lnode->setName("Light1");
    lnode->getTransform()->setTranslation(Vector3(250.0f, 250.0f, 50.0f));

    light = new Light();
    light->setIntensity(5.0f);
    light->setQuadratic(0.005f);

    lnode->addComponent("light_comp", light);

    test = new Sprite("casa_diffuse.png", "casa_normal.png");
    test->setName("logo");
    test->getTransform()->setTranslation(Vector3(150.0f, 150.0f, 0.0f));
    test->attachScript(new Script(readFile("move.lua"), win->getLuaEngine()));

    win->getTree()->addChild(test);
    win->getTree()->addChild(lnode);
}

int main(int argc, char** argv)
{
    // Create a GameWindow
    win = new GameWindow();
    win->createWindow(640, 480, "Test");

    // Set ambient color
    Color amb(0.2, 0.2, 0.2, 1.0);
    win->setAmbient(amb);

    // Set the resource-init function
    win->init = init;

    // Start game
    win->mainloop();

    // Free memory
    SAFE_DELETE(win);

    return 0;
}
