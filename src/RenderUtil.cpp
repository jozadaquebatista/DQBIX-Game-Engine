#include "..\include\RenderUtil.h"

void RenderUtil::clearScreen()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::initGraphics(int w, int h)
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, w, h);
}
