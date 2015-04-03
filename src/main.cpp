
#include "../include/GameWindow.h"
#include "../include/Text.h"
#include "../include/simplemove.h"
#include "../include/light.h"
#include "../include/assetpackage.h"
#include "../include/tilemap.h"

Sprite* stand;
GameWindow* win;
Light* light1, *light2;
Node* light_node, *light_node2;
AssetPackage* pak;
TileMap* map;

void init()
{    
    pak = new AssetPackage("exp.zip");

    map = new TileMap(pak->loadTexture("tile1.png"), pak->loadTexture("tile1_n.png"), 4, 4);
    map->setName("map");
    std::vector<Tile*> tls = {
        new Tile(Vector3(0.0, 5.0, 0.0), 1),
        new Tile(Vector3(1.0, 5.0, 0.0), 1),
        new Tile(Vector3(2.0, 5.0, 0.0), 1),
        new Tile(Vector3(3.0, 5.0, 0.0), 1),
        new Tile(Vector3(4.0, 5.0, 0.0), 1),
        new Tile(Vector3(5.0, 5.0, 0.0), 1),
        new Tile(Vector3(6.0, 5.0, 0.0), 1),
        new Tile(Vector3(7.0, 5.0, 0.0), 1),
        new Tile(Vector3(8.0, 5.0, 0.0), 1),
        new Tile(Vector3(9.0, 5.0, 0.0), 1)
    };

    map->addTiles(tls);
    map->getTransform()->setScale(Vector3(4.0f, 4.0f, 1.0f));

    light1 = new Light();
    light1->setIntensity(40.0f);
    light1->setColor(1.0f, 0.4f, 0.2f);
    light1->setQuadratic(0.005f);

    light2 = new Light();
    light2->setIntensity(30.0f);
    light2->setColor(0.3f, 0.4f, 1.0f);
    light2->setQuadratic(0.005f);

    light_node = new Node();
    light_node->setName("Light1");
    light_node->getTransform()->setTranslation(Vector3(200.0f, 200.0f, 40.0f));
    light_node->addComponent("Light_comp1", light1);

    light_node2 = new Node();
    light_node2->setName("Light2");
    light_node2->getTransform()->setTranslation(Vector3(400.0f, 200.0f, 60.0f));
    light_node2->addComponent("Light_comp2", light2);

    stand = new Sprite(pak->loadTexture("stand.png"), pak->loadTexture("standn.png"));
    stand->setName("standchar");
    stand->getTransform()->setTranslation(Vector3(170.0f, 294.0f, 0.0f));
    stand->getTransform()->setScale(Vector3(4.0f, 4.0f, 1.0f));

    win->getTree()->addChild(map);
    win->getTree()->addChild(stand);
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
    SAFE_DELETE(pak);

    return 0;
}
