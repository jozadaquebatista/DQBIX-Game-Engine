#include "../include/Node.h"
#include "../include/GameWindow.h"
#include "../include/SceneTree.h"

#include <typeinfo>

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

    for (auto& comp : m_components)
    {
        comp.second->destroy();
    }

    for (auto& ob : m_children)
	{
		SAFE_DELETE(ob);
	}
    for (auto& comp : m_components)
    {
        SAFE_DELETE(comp.second);
    }

	SAFE_DELETE(m_transform);
    SAFE_DELETE(m_script);
}

Node* Node::addChild(Node* obj)
{
    obj->setEngine(this->win);
	obj->setParentNode(this);
    obj->getTransform()->setParent(this->getTransform());
    m_children.push_back(obj);
    return this;
}

Node* Node::addComponent(std::string name, Component *comp)
{
    std::map<std::string, Component*>::const_iterator pos = m_components.find(name);
    if (pos == m_components.cend())
    {
        comp->setOwner(this);
        m_components.insert({name, comp});
        return this;
    }
    return NULL;
}

void Node::drawAll(SceneTree* tree)
{
    draw(tree);

	for (auto& ob : m_children)
	{
        ob->drawAll(tree);
	}
}

void Node::draw(SceneTree* tree)
{
    for (auto& comp : m_components)
    {
        comp.second->draw(tree);
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
    this->win = win;

    for (auto& comp : m_components)
    {
        comp.second->addToEngine(win);
    }
    for (auto& n : m_children)
    {
        n->setEngine(win);
    }
}

GameWindow *Node::getEngine()
{
    return this->win;
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

luabridge::LuaRef Node::getComponents(lua_State *L) const
{
    using namespace luabridge;
    LuaRef ret = newTable(L);
    for (auto& c : m_components)
    {
        auto sec = c.second;
        if (IsType<Light>(sec))
            ret[c.first] = (Light*)c.second;
        else if (IsType<AudioClip>(sec))
            ret[c.first] = (AudioClip*)c.second;
        else
            ret[c.first] = c.second;
    }
    return ret;
}

void Node::update(float delta)
{
	getTransform()->update();

    if (m_script != NULL)
        m_script->update(delta);
    for (auto& comp : m_components)
    {
        comp.second->update(delta);
    }
}

void Node::create()
{
    if (m_script != NULL)
        m_script->init();

    for (auto& comp : m_components)
    {
        comp.second->create();
    }
}

void Node::createAll()
{
    create();

    for (Node*& ob : m_children)
    {
        ob->createAll();
    }
}

void Node::attachScript(Script *scr)
{
    if (scr != NULL)
    {
        m_script = scr;
        m_script->setOwner(this);
        m_script->compile();
    }
    else { m_script = NULL; }
}

void Node::RegisterObject(lua_State* L)
{
    using namespace luabridge;

    getGlobalNamespace(L)
        .beginClass<Node>("Node")
        .addConstructor<void(*)(void)>()
        .addFunction("addchild", &Node::addChild)
        .addFunction("getnode", &Node::getNode)
        .addFunction("gettransform", &Node::getTransform)
        .addFunction("getname", &Node::getName)
        .addFunction("rename", &Node::setName)
        .addFunction("getparent", &Node::getParentNode)
        .addFunction("setparent", &Node::setParentNode)
        .addFunction("getchildren", &Node::getChildren)
        .addFunction("getcomponents", &Node::getComponents)
        .endClass();
}
