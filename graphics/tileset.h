#ifndef __IX_TILEMAP__
#define __IX_TILEMAP__
#pragma once

#include "image.h"
class tileset
{
public:
	tileset(image* map = NULL, int rows = 1, int cols = 1, std::string strmap = "");

	image* getTile(char c);

	image* getTileSet() const { return m_map; }
	void setTileSet(image* val) { m_map = val; }
	std::string getStringMap() const { return m_strmap; }
	void setStringMap(std::string val) { m_strmap = val; }
	int getRows() const { return m_rows; }
	void setRows(int val) { m_rows = val; }
	int getCols() const { return m_cols; }
	void setCols(int val) { m_cols = val; }

	virtual ~tileset();

	static void lua_reg(lua_State* L);
public:
	int m_rows, m_cols;
	std::string m_strmap;
	image* m_map;	
};

#endif // __IX_TILEMAP__