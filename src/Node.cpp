#include "..\include\Node.h"

Node::Node()
{
	m_transform = new Transform();
}

Node::~Node()
{
	if (m_script == nullptr) return;
		m_script->destroy();

	for (auto& ob : m_children)
	{
		SAFE_DELETE(ob);
	}

	SAFE_DELETE(m_transform);
	SAFE_DELETE(m_script);
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

void Node::attachScript(Script* scr)
{
	if (scr != nullptr)
	{
		scr->setOwner(this);
		m_script = scr;
		m_script->compile();
	}
	else { m_script = nullptr; }
}

void Node::RegisterObject(lua_State* L)
{
	using namespace luabridge;

	getGlobalNamespace(L)
		.beginClass<Node>("Node")
		.addConstructor<void(*)(void)>()
		.addFunction("addChild", &Node::addChild)
		.addFunction("getNode", &Node::getNode)
		.addProperty("transform", &Node::getTransform)
		.addProperty("name", &Node::getName, &Node::setName)
		.endClass();
}

void Node::update(float delta)
{
	getTransform()->update();
	if (m_script == nullptr) return;
		m_script->update(delta);
}

void Node::create()
{
	if (m_script == nullptr) return;

	m_script->init();
}
