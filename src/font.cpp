#include "../include/font.h"

Font::Font()
    : fnth(0)
{

}

Font::Font(std::string filename, int sz)
{
    fnth = dtx_open_font(filename.c_str(), sz);
    this->sz = sz;

    dtx_vertex_attribs(0, 1);
}

Font::~Font()
{
    if (fnth) dtx_close_font(fnth);
}

void Font::draw(std::string text)
{
    dtx_string(text.c_str());
    dtx_flush();
}

void Font::use()
{
    if (!fnth) return;
    dtx_use_font(fnth, sz);
}

