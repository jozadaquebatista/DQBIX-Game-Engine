#include "../include/RenderUtil.h"

void RenderUtil::clearScreen()
{
	glClearColor(m_backcolor.r, m_backcolor.g, m_backcolor.b, m_backcolor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderUtil::initGraphics(int w, int h)
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);

	glFrontFace(GL_CW);

	glViewport(0, 0, w, h);
}

void RenderUtil::setBackColor(vec4 col)
{
	m_backcolor = col;
}

glm::vec4 RenderUtil::m_backcolor;
