#ifndef __IX_FONT__
#define __IX_FONT__
#pragma once

#include "point.hpp"
#include "Node.h"

#include "font.h"

class Text : public Node
{

public:
	Text(string fontfile = "", int sz = 18);
    Text(Font* f);

    void draw(SceneTree* tree);

	string getText() const { return m_text; }
	void setText(string t) { m_text = t; }

    Font *getFont() const;
    void setFont(Font *getFont);

	Color getColor() const { return m_color; }
	void setColor(Color c) { m_color = c; }
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

    Font* m_font;
	Shader* m_shader;
	Color m_color;
	string m_text;
};

#endif // __IX_FONT__
