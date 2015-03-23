#ifndef __IX_FONT__
#define __IX_FONT__
#pragma once

#include "point.hpp"
#include "Node.h"

#include <drawtext.h>

class Text : public Node
{
public:
	Text(std::string fontfile = "", int sz = 18);

	point* measure_string(std::string str);
	void set_range(int from, int to);
	void use();

	void draw();

	std::string getText() const { return m_text; }
	void setText(std::string t) { m_text = t; }

	color getColor() const { return m_color; }
	void setColor(color c) { m_color = c; }
	void setColor(float r, float g, float b, float a)
	{
		m_color.r = r;
		m_color.g = g;
		m_color.b = b;
		m_color.a = a;
	}

	virtual ~Text();

private:
	void operator=(Text f) {}
        Text(Text&) {}

	int sz;
	struct dtx_font* fnth;
	Shader* m_shader;
	color m_color;
	std::string m_text;
};

#endif // __IX_FONT__
