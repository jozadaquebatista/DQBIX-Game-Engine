#include "../include/font.h"

point* font::measure_string(std::string str)
{
	if (!fnth) return NULL;
	use();
	float w, h;
	w = dtx_string_width(str.c_str());
	h = dtx_string_height(str.c_str());
	return new point(w, h);
}

void font::draw(std::string text, mat4 model, mat4 proj, color* col)
{
	use();
	dtx_string(text.c_str());
	dtx_flush();

	m_shader->use();
	m_shader->setInt("image", 0);
	m_shader->setVec3("color", col->r, col->g, col->b);
	m_shader->setMatrix("model", model);
	m_shader->setMatrix("proj", proj);

	glUseProgram(0);
}

void font::set_range(int from, int to)
{
	if (!fnth) return;
	dtx_prepare_range(fnth, sz, from, to);
}

void font::use()
{
	if (!fnth) return;
	dtx_use_font(fnth, sz);
}

font::~font()
{
	if (fnth) dtx_close_font(fnth);
}

font::font(std::string fontfile /*= ""*/, int sz/*=18*/)
{
	fnth = dtx_open_font(fontfile.c_str(), sz);
	dtx_vertex_attribs(0, 1);

	this->sz = sz;

	m_shader = new shader();
	m_shader->fromString(text_vert, text_frag);

	m_shader->compile();
	m_shader->addCommonUniforms();
	m_shader->addUniform("image");
	m_shader->addUniform("color");
}
