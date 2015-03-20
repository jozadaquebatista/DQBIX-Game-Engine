#include "..\include\Node.h"

Node::Node()
{
	m_transform = new Transform();
}


Node::~Node()
{
	for (auto& ob : m_children)
	{
		SAFE_DELETE(ob);
	}

	SAFE_DELETE(m_transform);
}

Node* Node::addChild(Node* obj)
{
	m_children.push_back(obj);
	obj->getTransform()->setParent(getTransform());
	return this;
}

void Node::drawAll()
{
	draw();

	for (auto& ob : m_children)
	{
		ob->drawAll();
	}

	updateAll();
}

void Node::updateAll()
{
	update();

	for (auto& ob : m_children)
	{
		ob->updateAll();
	}
}

void Node::update()
{
	m_transform->update();
}
