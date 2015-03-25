#include "..\include\Node.h"
#include "../include/GameWindow.h"

Node::Node()
{
	m_transform = new Transform();
    m_parentnode = NULL;
}

Node::~Node()
{
//    if (m_script != NULL)
//        m_script->destroy();
    for (auto& comp : m_components)
    {
        comp->destroy();
    }

    for (auto& ob : m_children)
	{
		SAFE_DELETE(ob);
	}
    for (auto& comp : m_components)
    {
        SAFE_DELETE(comp);
    }

	SAFE_DELETE(m_transform);
}

Node* Node::addChild(Node* obj)
{
	m_children.push_back(obj);
    obj->setEngine(this->win);
	obj->setParentNode(this);
	obj->getTransform()->setParent(getTransform());
    return this;
}

Node* Node::addComponent(Component *comp)
{
    comp->setOwner(this);
    m_components.push_back(comp);
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

void Node::draw()
{
    for (auto& comp : m_components)
    {
        comp->draw();
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

void Node::setEngine(GameWindow *win)
{
    if (this->win != win)
    {
        this->win = win;

        for (auto& comp : m_components)
        {
            comp->addToEngine(win);
        }
        for (auto& n : m_children)
        {
            n->setEngine(win);
        }
    }
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

void Node::update(float delta)
{
	getTransform()->update();
//    if (m_script != NULL)
//		m_script->update(delta);
    for (auto& comp : m_components)
    {
        comp->update(delta);
    }
}

void Node::create()
{
//    if (m_script != NULL)
//        m_script->init();
    for (auto& comp : m_components)
    {
        comp->create();
    }
}

void Node::createAll()
{
    create();

    for (auto& ob : m_children)
    {
        ob->createAll();
    }
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
