#include "../include/tileset.h"

tileset::tileset(image* map /*= NULL*/, int rows /*= 1*/, int cols /*= 1*/, std::string strmap /*= ""*/)
{
	m_rows = rows;
	m_cols = cols;
	m_map = map;
	m_strmap = strmap;
}

image* tileset::getTile(char c)
{
	std::size_t pos = m_strmap.find(c);
	if (pos != std::string::npos)
	{
		int i = static_cast<int>(pos);

		int w = m_map->getResource()->getWidth() / m_cols;
		int h = m_map->getResource()->getHeight() / m_rows;

		int ax = i % m_cols * w;
		int ay = (int)(i / m_cols) * h;

		rect clip;
		clip.x = ax;
		clip.y = ay;
		clip.w = w;
		clip.h = h;
		clip.rows = m_rows;
		clip.cols = m_cols;
		m_map->setCliprect(clip);
		return m_map;
	}
	return NULL;
}

tileset::~tileset()
{
	if (m_map) delete m_map;
}

void tileset::lua_reg(lua_State* L)
{
	using namespace luabridge;

	getGlobalNamespace(L)
		.beginClass<tileset>("tileset")
		.addConstructor<void(*)(image*, int, int, std::string)>()
		.addFunction("tile", &tileset::getTile)
		.addProperty("rows", &tileset::getRows, &tileset::setRows)
		.addProperty("cols", &tileset::getCols, &tileset::setCols)
		.addProperty("stringmap", &tileset::getStringMap, &tileset::setStringMap)
		.addProperty("tileset", &tileset::getTileSet, &tileset::setTileSet)
		.endClass();
}
