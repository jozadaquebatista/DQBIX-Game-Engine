#include "renderer.h"

void renderer::blit_full(image* img, int x, int y, float sx, float sy, float a)
{
	if (img == NULL) return;

	glColor4f(screen_mgr::drawcolor->r,
		screen_mgr::drawcolor->g,
		screen_mgr::drawcolor->b,
		screen_mgr::drawcolor->a);
	glPushMatrix();

	int w = img->getCliprect().w;
	int h = img->getCliprect().h;

	float crw = (float)img->getCliprect().w / (float)img->getResource()->getWidth();
	float crh = (float)img->getCliprect().h / (float)img->getResource()->getHeight();
	float crx = (float)img->getCliprect().x / (float)img->getResource()->getWidth();
	float cry = (float)img->getCliprect().y / (float)img->getResource()->getHeight();

	float px = (float)x / (float)w;
	float py = (float)y / (float)h;
	float sw = w * sx;
	float sh = h * sy;

	/*glTranslatef(x, y, 0);
	glScalef(sw, sh, 1.0f);
	glRotatef(a, 0, 0, 1);*/
	Matrix4 m;
	m.rotateZ(a).scale(sw, sh, 1.0f).translate(x, y, 0);
	glMultMatrixf(m.get());


	glEnable(GL_TEXTURE_2D);
	img->bind();

	glBegin(GL_QUADS);

	glTexCoord2f(crx,         cry); glVertex2f(0, 0);
	glTexCoord2f(crx+crw,     cry); glVertex2f(1.0f, 0);
	glTexCoord2f(crx+crw, cry+crh); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(crx,     cry+crh); glVertex2f(0, 1.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	//img->draw_full(x, y, sx, sy, a);
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
	glPushMatrix();

	fnt->use();
	Matrix4 m;
	m.scale(1.0f, -1.0f, 1.0f).translate(x, y, 0);
	glMultMatrixf(m.get());

	dtx_string(text.c_str());

	glPopMatrix();
}

void renderer::drawtextr(std::string text, int x, int y, float a, font* fnt)
{
	if (!fnt) return;
	glColor4f(screen_mgr::drawcolor->r,
		screen_mgr::drawcolor->g,
		screen_mgr::drawcolor->b,
		screen_mgr::drawcolor->a);
	glPushMatrix();

	fnt->use();
	Matrix4 m;
	m.rotateZ(a).scale(1.0f, -1.0f, 1.0f).translate(x, y, 0);
	glMultMatrixf(m.get());

	dtx_string(text.c_str());

	glPopMatrix();
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
