#include "../include/imageResource.h"

imageResource::imageResource(int target, int width, int height, int numtex, unsigned char* data, int filter, int internalFormat, int format, bool clamp, int attachment)
{
	this->m_numTextures = numtex;
	this->m_refCount = 1;
	this->m_target = target;
	this->m_width = width;
	this->m_height = height;
	this->m_fbo = 0;

	this->initTextures(data, filter, internalFormat, format, clamp);
	this->initRenderTargets(attachment);
}

imageResource::~imageResource()
{
	if (&m_id) glDeleteTextures(1, (GLuint*)&m_id);
	if (m_fbo) glDeleteFramebuffers(1, (GLuint*)&m_fbo);
}

void imageResource::initTextures(unsigned char* data, int filter, int internalFormat, int format, bool clamp)
{
	glGenTextures(1, &m_id);

	glBindTexture(getTarget(), m_id);

	glTexParameterf(getTarget(), GL_TEXTURE_MIN_FILTER, filter);
	glTexParameterf(getTarget(), GL_TEXTURE_MAG_FILTER, filter);

	if (clamp)
	{
		glTexParameteri(getTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(getTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else
	{
		glTexParameteri(getTarget(), GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(getTarget(), GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexImage2D(getTarget(), 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

}

void imageResource::initRenderTargets(int attachment)
{
	if (attachment == NULL) return;

	if (m_fbo == 0)
	{
		glGenFramebuffers(1, (GLuint*)&m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, getTarget(), m_id, 0);
	if (m_fbo == 0) return;

    GLenum drawBuffers[1] = {attachment};

    glReadBuffer(GL_NONE);
    glDrawBuffers(1, drawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
        printf("Could not create render targets.");
		exit(EXIT_FAILURE);
	}
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(getTarget(), 0);
}

void imageResource::use()
{
	glBindTexture(getTarget(), m_id);
}

void imageResource::useAsRenderTarget()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
}

void imageResource::setFilter(int flt)
{
    glBindTexture(getTarget(), m_id);

    glTexParameterf(getTarget(), GL_TEXTURE_MIN_FILTER, flt);
    glTexParameterf(getTarget(), GL_TEXTURE_MAG_FILTER, flt);
}

void imageResource::addReference()
{
	m_refCount++;
}

bool imageResource::removeReference()
{
	m_refCount--;
	return m_refCount == 0;
}

GLuint imageResource::getID()
{
	return m_id;
}

int* imageResource::genTextures(int count)
{
	int* res = new int[count];
	for (int i = 0; i < count; i++)
		glGenTextures(1, (GLuint*)&res[i]);
	return res;
}
