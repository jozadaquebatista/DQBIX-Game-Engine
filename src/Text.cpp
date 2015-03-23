#include "../include/Text.h"
#include "../include/GameWindow.h"

point* Text::measure_string(std::string str)
{
	if (!fnth) return NULL;
	use();
	float w, h;
	w = dtx_string_width(str.c_str());
	h = dtx_string_height(str.c_str());
	
	return new point(w, h);
}

void Text::draw()
{
	if (!fnth) return;

	use();
#ifdef MODERN_OPENGL
	if (m_shader != nullptr)
	{
		m_shader->use();
		m_shader->setInt("image", 0);
		m_shader->setVec4("color", m_color.r, m_color.g, m_color.b, m_color.a);
		m_shader->setMatrix("model", getTransform()->getTransformation());
		m_shader->setMatrix("proj", GameWindow::Projection);
	}

	dtx_string(m_text.c_str());
	dtx_flush();

	glUseProgram(0);
#else
    glPushMatrix();

    glMultMatrixf(value_ptr(getTransform()->getTransformation()));

    dtx_string(m_text.c_str());

    glPopMatrix();
#endif

}

void Text::set_range(int from, int to)
{
	if (!fnth) return;
	dtx_prepare_range(fnth, sz, from, to);
}

void Text::use()
{
	if (!fnth) return;
	dtx_use_font(fnth, sz);
}

Text::~Text()
{
	if (fnth) dtx_close_font(fnth);
}

Text::Text(std::string fontfile /*= ""*/, int sz/*=18*/)
{
	fnth = dtx_open_font(fontfile.c_str(), sz);
#ifdef MODERN_OPENGL
	dtx_vertex_attribs(0, 1);
#endif
	this->sz = sz;

#ifdef MODERN_OPENGL
	m_shader = new Shader();
	m_shader->fromString(text_vert, text_frag);

	m_shader->compile();
	m_shader->addCommonUniforms();
	m_shader->addUniform("image");
	m_shader->addUniform("color");
#endif
}
