#ifndef TILEMAP_H
#define TILEMAP_H
#pragma once

#include "Sprite.h"

typedef struct Tile
{
    Vector3 position;
    int index;

    Tile(Vector3 pos, int i)
    {
        position = pos;
        index = i;
    }
    ~Tile() {}
} Tile;

class TileMap
        : public Sprite
{
public:

    TileMap(Texture* tileset = 0, int rows = 0, int cols = 0);
    TileMap(Texture* tileset = 0, Texture* tileset_norm = 0, int rows = 0, int cols = 0);

    void addTile(Tile* ntile);
    void addTiles(std::vector<Tile*> ntiles);
private:
    std::vector<Tile*> m_tiles;
    Mesh* m_tilemesh;

    // TileMap Settings
    int rows, cols;

    void generate_mesh();
};

#endif // TILEMAP_H
