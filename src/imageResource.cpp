#include "../include/imageResource.h"

imageResource::imageResource(int target, int width, int height, int numtex, unsigned char** data, int* filter, int* internalFormats, int* formats, bool clamp, int* attachments)
{
	this->m_numTextures = numtex;
	this->m_refCount = 1;
	this->m_target = target;
	this->m_width = width;
	this->m_height = height;
	this->m_fbo = 0;

	this->initTextures(data, filter, internalFormats, formats, clamp);
	this->initRenderTargets(attachments);
}

imageResource::~imageResource()
{
	if (*m_id) glDeleteTextures(m_numTextures, (GLuint*)&m_id);
	if (m_fbo) glDeleteFramebuffers(1, (GLuint*)&m_fbo);
	if (m_id) delete[] m_id;
}

void imageResource::initTextures(unsigned char** data, int* filter, int* internalFormats, int* formats, bool clamp)
{
	this->m_id = genTextures(m_numTextures);

	for (int i = 0; i < m_numTextures; i++)
	{
		glBindTexture(getTarget(), m_id[i]);

		glTexParameterf(getTarget(), GL_TEXTURE_MIN_FILTER, filter[i]);
		glTexParameterf(getTarget(), GL_TEXTURE_MAG_FILTER, filter[i]);

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

		glTexImage2D(getTarget(), 0, internalFormats[i], m_width, m_height, 0, formats[i], GL_UNSIGNED_BYTE, data[i]);

	}
}

void imageResource::initRenderTargets(int* attachments)
{
	if (attachments == NULL) return;

	int* drawBuffers = new int[32];

	for (int i = 0; i < m_numTextures; i++)
	{
		drawBuffers[i] = attachments[i];

		if (m_fbo == 0)
		{
			glGenFramebuffers(1, (GLuint*)&m_fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachments[i], getTarget(), m_id[i], 0);
	}
	if (m_fbo == 0) return;
	glDrawBuffers(32, (const GLenum*)&drawBuffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		exit(EXIT_FAILURE);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void imageResource::use(int ind)
{
	if (m_id[ind])
		glBindTexture(getTarget(), m_id[ind]);
}

void imageResource::useAsRenderTarget()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, m_width, m_height);
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

int imageResource::getID()
{
	return m_id[0];
}

int* imageResource::genTextures(int count)
{
	int* res = new int[count];
	for (int i = 0; i < count; i++)
		glGenTextures(1, (GLuint*)&res[i]);
	return res;
}
