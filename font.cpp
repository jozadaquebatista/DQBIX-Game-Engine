#include "font.h"

point* font::measure_string(std::string str)
{
	if (!fnth) return NULL;
	use();
	float w, h;
	w = dtx_string_width(str.c_str());
	h = dtx_string_height(str.c_str());
	return new point(w, h);
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
	this->sz = sz;
}
