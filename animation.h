#ifndef __IX_ANIMATION__
#define __IX_ANIMATION__
#pragma once

#include <vector>
#include <initializer_list>
#include "image.h"

class Stopwatch;
class animation
{
public:
	animation() {}
	animation(image* sheet = NULL, int rows = 1, int cols = 1, float speed = 0, bool loop = false);
	
	image* step();

	int getRows() const { return m_rows; }
	void setRows(int val) { m_rows = val; }
	int getCols() const { return m_cols; }
	void setCols(int val) { m_cols = val; }
	float getSpeed() const { return m_speed; }
	void setSpeed(float val) { m_speed = val; }
	bool getLoop() const { return m_loop; }
	void setLoop(bool val) { m_loop = val; }
	image* getSpriteSheet() const { return m_sheet; }
	void setSpriteSheet(image* val) { m_sheet = val; }
	int getIndex() const { return m_index; }

	virtual ~animation();

	static void lua_reg(lua_State* L);

private:
	int m_rows, m_cols;
	int m_index;	
	float m_speed;
	bool m_loop;

	image* m_sheet;	
	
	Stopwatch* sw;

	animation(animation& anim) {}
	void operator=(animation texture) {}

};

#endif //__IX_ANIMATION__