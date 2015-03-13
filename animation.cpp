#include "animation.h"
#include "Stopwatch.hpp"

animation::animation(image* sheet /*= NULL*/, int rows /*= 1*/, int cols /*= 1*/, float speed /*= 0*/, bool loop /*= false*/)
{
	m_sheet = sheet;
	m_loop = loop;
	m_cols = cols;
	m_rows = rows;
	m_speed = speed;
	m_index = 0;
	sw = new Stopwatch();
	sw->Start();
}

void animation::lua_reg(lua_State* L)
{
	using namespace luabridge;

	getGlobalNamespace(L)
		.beginClass<animation>("animation")
		.addConstructor<void(*)(image*, int, int, float, bool)>()
		.addFunction("step", &animation::step)
		.addProperty("rows", &animation::getRows, &animation::setRows)
		.addProperty("cols", &animation::getCols, &animation::setCols)
		.addProperty("loop", &animation::getLoop, &animation::setLoop)
		.addProperty("spritesheet", &animation::getSpriteSheet, &animation::setSpriteSheet)
		.addProperty("speed", &animation::getSpeed, &animation::setSpeed)
		.addProperty("frameindex", &animation::getIndex)
		.endClass()
		.beginClass<std::vector<int>>("ivector")
		.addFunction("size", &std::vector<int>::size)
		.addFunction("empty", &std::vector<int>::empty)
		.addFunction<std::vector<int>::reference(std::vector<int>::*)(std::vector<int>::size_type)>("get", &std::vector<int>::at)
		.addFunction<std::vector<int>::const_reference(std::vector<int>::*)(std::vector<int>::size_type) const>("get", &std::vector<int>::at)
		.endClass();
		
	Stopwatch::lua_reg(L);
}

image* animation::step()
{
	if (m_index < 0) m_index = 0;
	if (m_sheet == NULL) return NULL;
	if (m_cols <= 0 || m_rows <= 0) return NULL;

	int fc = m_rows * m_cols;
	if (sw->ElapsedMillis() >= (int)(100.0f * m_speed))
	{
		sw->Restart();
		if (m_index++ >= fc - 1)
		{
			if (m_loop)
				m_index = 0;
			else
				m_index = fc - 1;
		}
	}
	int i = 0;
	i = m_index;

	int w = m_sheet->getResource()->getWidth() / m_cols;
	int h = m_sheet->getResource()->getHeight() / m_rows;

	int ax = i % m_cols * w;
	int ay = (int)(i / m_cols) * h;

	// printf("%d, %d, %d, %d\n", ax, ay, w, h);

	rect clip;
	clip.x = ax;
	clip.y = ay;
	clip.w = w;
	clip.h = h;
	m_sheet->setCliprect(clip);
	return m_sheet;
}

animation::~animation()
{
	if (m_sheet) delete m_sheet;
	m_sheet = NULL;
}
