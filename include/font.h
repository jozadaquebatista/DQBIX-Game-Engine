#ifndef FONT_H
#define FONT_H

#include <string>
#define GL_ES
#include <drawtext.h>
class Font
{
public:
    Font();
    Font(string filename, int sz);
    ~Font();

    void draw(string text);
    void use();
private:
    int sz;
    struct dtx_font* fnth;
};

#endif // FONT_H
