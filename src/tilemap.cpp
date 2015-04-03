#include "../include/tilemap.h"

TileMap::TileMap(Texture *tileset, int rows, int cols)
    : Sprite(tileset)
{
    setMaterial(new Material(tileset));
    this->rows = rows;
    this->cols = cols;
}

TileMap::TileMap(Texture *tileset, Texture *tileset_norm, int rows, int cols)
   : Sprite(tileset, tileset_norm)
{
    setMaterial(new Material(tileset, tileset_norm));
    this->rows = rows;
    this->cols = cols;
}

void TileMap::addTile(Tile* ntile)
{
    m_tiles.push_back(ntile);
    generate_mesh();
}

void TileMap::addTiles(std::vector<Tile*> ntiles)
{
    for (Tile*& t : ntiles)
        m_tiles.push_back(t);

    if (ntiles.size() > 0)
        generate_mesh();
}

void TileMap::generate_mesh()
{
    m_tilemesh = new Mesh();
    std::vector<vertex> verts;
    std::vector<int> ind;

    for (int i = 0; i < m_tiles.size(); i++)
    {
        Tile* t = m_tiles[i];

        int w = getMaterial()->getDiffuseTexture()->getResource()->getWidth() / cols;
        int h = getMaterial()->getDiffuseTexture()->getResource()->getHeight() / rows;

        int ax = t->index % cols * w;
        int ay = (int)(t->index / cols) * h;

        rect clip;
        clip.x = ax;
        clip.y = ay;
        clip.w = w;
        clip.h = h;
        clip.frame = t->index;
        clip.cols = cols;
        clip.rows = rows;

        vec4 r = getMaterial()->getDiffuseTexture()->transformRect(clip);

        float px = t->position.x * (float)w;
        float py = t->position.y * (float)h;

        verts.push_back(vertex(vec3(px, py, 0.0f), vec2(r.x, r.y)));
        verts.push_back(vertex(vec3(w + px, py, 0.0f), vec2(r.x+r.z, r.y)));
        verts.push_back(vertex(vec3(w + px, h + py, 0.0f), vec2(r.x+r.z, r.y+r.w)));
        verts.push_back(vertex(vec3(px, h + py, 0.0f), vec2(r.x, r.y+r.w)));

        for (int j = 0; j < 4; j++)
        {
            ind.push_back(j + (i*4));
        }
    }

    m_tilemesh->addVertices(verts, ind);

    getMaterial()->getDiffuseTexture()->setShape(m_tilemesh);
    getMaterial()->getNormalTexture()->setShape(m_tilemesh);
}
