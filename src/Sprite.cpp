#include "../include/Sprite.h"
#include "../include/GameWindow.h"

Sprite::Sprite(std::string filename)
{
	m_texture = filename != "" ? new Texture(filename) : NULL;

	m_shader = new shader();
	m_shader->fromString(default_vert, default_frag);

	m_shader->compile();
	m_shader->addCommonUniforms();
	m_shader->addUniform("image");
	m_shader->addUniform("cliprect");
}


Sprite::~Sprite()
{
	SAFE_DELETE(m_texture);
	SAFE_DELETE(m_shader);
}

void Sprite::draw()
{
	if (!m_texture) return;

	vec4 tr = m_texture->getTransformedClipRect();

	m_texture->bind();

	if (m_shader != nullptr)
	{
		m_shader->use();
		m_shader->setInt("image", 0);
		m_shader->setVec4("cliprect", tr.x, tr.y, tr.z, tr.w);
		m_shader->setMatrix("model", getTransform()->getTransformation());
		m_shader->setMatrix("proj", GameWindow::Projection);
	}

	m_texture->getShape()->draw(GL_TRIANGLE_STRIP);

	glUseProgram(0);
}
