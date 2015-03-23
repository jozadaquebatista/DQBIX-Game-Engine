#include "..\include\Node.h"

Node::Node()
{
	m_transform = new Transform();
    m_parentnode = NULL;
    m_script = NULL;
}

Node::~Node()
{
    if (m_script != NULL)
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
    name = newname;
}

Node* Node::getNode(std::string name)
{
	for (auto& n : m_children)
	{
		if (n->getName() == name)
			return n;
	}
    return NULL;
}

luabridge::LuaRef Node::getChildren(lua_State* L) const
{
    using namespace luabridge;
    LuaRef ret = newTable(L);
    for (int i = 0; i < m_children.size(); i++)
    {
        Node* c = m_children[i];
        ret[i] = c;
    }
    return ret;
}

void Node::attachScript(Script* scr)
{
	if (scr != nullptr)
	{
		m_script = new Script(*scr);
		m_script->setOwner(this);
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
        .addFunction("getname", &Node::getName)
        .addFunction("rename", &Node::setName)
        .addFunction("getparent", &Node::getParentNode)
        .addFunction("setparent", &Node::setParentNode)
        .addFunction("getchildren", &Node::getChildren)
		.endClass();
}

void Node::update(float delta)
{
	getTransform()->update();
    if (m_script != NULL)
		m_script->update(delta);
}

void Node::create()
{
    if (m_script != NULL)
        m_script->init();
}

void Node::createAll()
{
    create();

    for (auto& ob : m_children)
    {
        ob->createAll();
    }
}
