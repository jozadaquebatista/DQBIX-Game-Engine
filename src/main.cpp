
#include "../include/GameWindow.h"
#include "../include/Text.h"
#include "../include/simplemove.h"
#include "../include/light.h"
#include "../include/assetpackage.h"
#include "../include/tilemap.h"

// Vars ///////
GameWindow* win;
Light* light1, *light2;
Node* light_node, *light_node2;

TileMap* map;

typedef struct Player
{
    AnimatedSprite* me;
    Player() {}
} Player;

void init()
{    
    // The Player //////////////
    Player player;
    player.me = new AnimatedSprite(new Texture("data/player.png"), new Texture("data/player_n.png"), 4, 4);
    player.me->setEngine(win);

    player.me->addAnimation(new Animation("stand", {4}, 0.1f, false));
    player.me->addAnimation(new Animation("run", {0, 1, 2, 3}, 0.09f, true));
    player.me->setCurrentAnimation("stand");

    player.me->getTransform()->setTranslation(Vector3(200.0f, 290.0f, 0.0f));
    player.me->getMaterial()->setShadeless(true);
    player.me->getMaterial()->getDiffuseTexture()->setFilter(GL_NEAREST);
    player.me->getMaterial()->getNormalTexture()->setFilter(GL_NEAREST);

    player.me->attachScript(new Script(readFile("player.lua"), win->getLuaEngine()));

    // The TileMap //////////////
    map = new TileMap(new Texture("data/tile1.png"), new Texture("data/tile1_n.png"), 4, 4);
    map->getMaterial()->setShadeless(true);
    map->getMaterial()->getDiffuseTexture()->setFilter(GL_NEAREST);
    map->getMaterial()->getNormalTexture()->setFilter(GL_NEAREST);
    map->setName("map");
    std::vector<Tile*> tls = {
        new Tile(Vector3(0.0, 5.0, 0.0), 0),
        new Tile(Vector3(1.0, 5.0, 0.0), 0),
        new Tile(Vector3(2.0, 5.0, 0.0), 0),
        new Tile(Vector3(3.0, 5.0, 0.0), 0),
        new Tile(Vector3(4.0, 5.0, 0.0), 0),
        new Tile(Vector3(5.0, 5.0, 0.0), 0),
        new Tile(Vector3(6.0, 5.0, 0.0), 0),
        new Tile(Vector3(7.0, 5.0, 0.0), 0),
        new Tile(Vector3(8.0, 5.0, 0.0), 0),
        new Tile(Vector3(9.0, 5.0, 0.0), 0)
    };
    map->addTiles(tls);
    map->getTransform()->setScale(Vector3(4.0f, 4.0f, 1.0f));

    // Some lights //////////////
    light1 = new Light();
    light1->setIntensity(30.0f);
    light1->setColor(1.0f, 0.4f, 0.2f);
    light1->setQuadratic(0.01f);

    light2 = new Light();
    light2->setIntensity(20.0f);
    light2->setColor(0.4f, 0.5f, 1.0f);
    light2->setQuadratic(0.01f);

    light_node = win->createNode();
    light_node->setName("Light1");
    light_node->getTransform()->setTranslation(Vector3(200.0f, 250.0f, 60.0f));
    light_node->addComponent("Light_comp1", light1);

    light_node2 = new Node();
    light_node2->setName("Light2");
    light_node2->getTransform()->setTranslation(Vector3(400.0f, 250.0f, 50.0f));
    light_node2->addComponent("Light_comp2", light2);

    // Add everything to the scene tree ////////

    win->getTree()->addChild(map);
    win->getTree()->addChild(light_node);
    win->getTree()->addChild(light_node2);
    win->getTree()->addChild(player.me);

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
