#include "../include/renderer.h"

void renderer::blit_full(image* img, int x, int y, float sx, float sy, float a)
{
	if (img == NULL) return;

	img->draw_full(x, y, sx, sy, a, screen_mgr::projection);
}

void renderer::blits(image* img, int x, int y, float sx, float sy)
{
	blit_full(img, x, y, sx, sy, 0.0f);
}

void renderer::blitr(image* img, int x, int y, float a)
{
	blit_full(img, x, y, 1.0f, 1.0f, a);
}

void renderer::blit(image* img, int x, int y)
{
	blit_full(img, x, y, 1.0f, 1.0f, 0.0f);
}

void renderer::drawtext(std::string text, int x, int y, font* fnt)
{
	if (!fnt) return;
	glColor4f(screen_mgr::drawcolor->r,
		screen_mgr::drawcolor->g,
		screen_mgr::drawcolor->b,
		screen_mgr::drawcolor->a);

	mat4 m = mat4(1.0f);
	m = translate(m, vec3((float)x, (float)y, 0.0f));
	
	fnt->draw(text, m, screen_mgr::projection, screen_mgr::drawcolor);
}

void renderer::drawtextr(std::string text, int x, int y, float a, font* fnt)
{
	if (!fnt) return;
	glColor4f(screen_mgr::drawcolor->r,
		screen_mgr::drawcolor->g,
		screen_mgr::drawcolor->b,
		screen_mgr::drawcolor->a);

	mat4 m = mat4(1.0f);
	m = translate(m, vec3((float)x, (float)y, 0.0f));
	m = rotate(m, a, vec3(0.0f, 0.0f, 1.0f));

	fnt->draw(text, m, screen_mgr::projection, screen_mgr::drawcolor);
}

void renderer::line(int x1, int y1, int x2, int y2)
{
	glColor4f(screen_mgr::drawcolor->r,
		screen_mgr::drawcolor->g,
		screen_mgr::drawcolor->b,
		screen_mgr::drawcolor->a);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

void renderer::dot(int x, int y)
{
	glColor4f(screen_mgr::drawcolor->r,
		screen_mgr::drawcolor->g,
		screen_mgr::drawcolor->b,
		screen_mgr::drawcolor->a);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void renderer::circle(int x, int y, int r, bool fill /*= false*/)
{
	glColor4f(screen_mgr::drawcolor->r,
		screen_mgr::drawcolor->g,
		screen_mgr::drawcolor->b,
		screen_mgr::drawcolor->a);
	if (!fill)
	{
		glBegin(GL_LINE_LOOP);
	}
	else
	{
		glBegin(GL_POLYGON);
	}
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * (float)i / (float)360;

		float _x = (float)r * cosf(theta);
		float _y = (float)r * sinf(theta);

		glVertex2f(_x + x, _y + y);
	}
	glEnd();
}

void renderer::rect(int x, int y, int w, int h, bool fill /*= false*/)
{
	glColor4f(screen_mgr::drawcolor->r,
		screen_mgr::drawcolor->g,
		screen_mgr::drawcolor->b,
		screen_mgr::drawcolor->a);
	if (!fill)
	{
		glBegin(GL_LINE_LOOP);
	}
	else
	{
		glBegin(GL_QUADS);
	}

	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glVertex2f(x+w, y+h);
	glVertex2f(x, y+h);
	if (!fill)
		glVertex2f(x, y);

	glEnd();
}
