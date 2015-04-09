#include "../include/GameWindow.h"
#include "../include/Text.h"

// Vars ///////
GameWindow* win;
Sprite* test;
Text* txt;

void init()
{
    test = new Sprite("logo.png");
    test->setName("logo");
    test->getMaterial()->setShadeless(true);
    test->getTransform()->setTranslation(Vector3(150.0f, 150.0f, 0.0f));
    test->attachScript(new Script(readFile("move.lua"), win->getLuaEngine()));

    txt = new Text("andy.ttf", 16);
    txt->setName("Label");
    txt->setText("Hello World!");
    txt->getTransform()->setTranslation(Vector3(48.0, 48.0, 0.0));

    win->getTree()->addChild(test);
    win->getTree()->addChild(txt);
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
