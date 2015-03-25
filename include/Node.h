// File: Node.h
// Class: Node
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_NODE__
#define __NIX_NODE__
#pragma once

#include "Transform.h"
#include "Texture.h"
#include "shader.h"
#include "component.h"
#include <vector>
#include "LuaEngine.hpp"

class GameWindow;
class Node
{
public:
	Node();
	~Node();

	Node* addChild(Node* obj);
    Node* addComponent(Component* comp);

	Transform* getTransform() const { return m_transform; }

	void drawAll();
    virtual void draw();
	virtual void update(float delta);
    virtual bool hovered(point mousepos) {return false;}

	void create();
    void createAll();

	void updateAll(float delta);

	void setName(std::string newname);
	std::string getName() const { return name; }

	Node* getNode(std::string name);

    Node* getParentNode() { return m_parentnode; }
	void setParentNode(Node* n) { m_parentnode = n; }

    void setEngine(GameWindow* win);

    luabridge::LuaRef getChildren(lua_State* L) const;

	static void RegisterObject(lua_State* L);
private:
	Node* m_parentnode;
	Transform* m_transform;
	std::vector<Node*> m_children;
    std::vector<Component*> m_components;
    std::string name;
    GameWindow* win;
};

#endif //__NIX_NODE__
