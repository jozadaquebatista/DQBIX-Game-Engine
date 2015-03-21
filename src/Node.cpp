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
	obj->setParentNode(this);
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
	
}

void Node::updateAll(float delta)
{
	update(delta);

	for (auto& ob : m_children)
	{
		ob->updateAll(delta);
	}
}

void Node::setName(std::string newname)
{
	if (getParentNode() == nullptr)
		name = newname;
	else
	{
		if (getParentNode()->getName() != newname)
			name = newname;
	}
}

Node* Node::getNode(std::string name)
{
	for (auto& n : m_children)
	{
		if (n->getName() == name)
			return n;
	}
	return nullptr;
}

void Node::update(float delta)
{
	getTransform()->update();
}
