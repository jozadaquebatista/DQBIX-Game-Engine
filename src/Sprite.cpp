#include "../include/Sprite.h"
#include "../include/GameWindow.h"

Sprite::Sprite()
{
	m_transform = new Transform();

	m_shader = new shader();
	m_shader->fromString(default_vert, default_frag);

	m_shader->compile();
	m_shader->addCommonUniforms();
	m_shader->addUniform("image");
	m_shader->addUniform("cliprect");
}


Sprite::~Sprite()
{
	for (auto& ob : m_children)
	{
		SAFE_DELETE(ob);
	}
	
	SAFE_DELETE(m_transform);
	SAFE_DELETE(m_texture);
}

Sprite* Sprite::addChild(Sprite* obj)
{
	m_children.push_back(obj);
	obj->getTransform()->setParent(getTransform());
	return this;
}

void Sprite::update()
{
	m_transform->update();
}

void Sprite::updateAll()
{
	update();

	for (auto& ob : m_children)
	{
		ob->updateAll();
	}
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

	m_texture->getShape()->draw();

	glUseProgram(0);
}

void Sprite::drawAll()
{
	draw();

	for (auto& ob : m_children)
	{
		ob->drawAll();
	}
}