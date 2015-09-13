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

class SceneTree;
class GameWindow;
class Node
{
public:
	Node();
    virtual ~Node();

	Node* addChild(Node* obj);
    Node* addComponent(std::string name, Component* comp);

	Transform* getTransform() const { return m_transform; }
    void setTransform(Transform* nt) { m_transform = nt; }

    void drawAll(SceneTree* tree);
    virtual void draw(SceneTree* tree);
	virtual void update(float delta);
    virtual bool hovered(Vector3 mousepos) {return false;}

	void create();
    void createAll();

	void updateAll(float delta);

	void setName(std::string newname);
	string getName() const { return name; }

	Node* getNode(std::string name);

    Node* getParentNode() { return m_parentnode; }
	void setParentNode(Node* n) { m_parentnode = n; }

    void setEngine(GameWindow* win);
    GameWindow* getEngine();

    void attachScript(Script *scr);

    luabridge::LuaRef getChildren(lua_State* L) const;
    luabridge::LuaRef getComponents(lua_State* L) const;

    static void RegisterObject(lua_State* L);

private:
	Node* m_parentnode;
	Transform* m_transform;
	vector<Node*> m_children;
    map<std::string, Component*> m_components;
    string name;
    GameWindow* win;

    Script* m_script;
};

#endif //__NIX_NODE__
