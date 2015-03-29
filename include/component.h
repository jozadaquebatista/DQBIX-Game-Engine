#ifndef __IX_COMPONENT_H
#define __IX_COMPONENT_H
#pragma once

#include "Script.h"
#include "Transform.h"

class SceneTree;
class GameWindow;
class Node;
class Component
{
public:
    Component();
    virtual ~Component();

    void setOwner(Node* own);
    Node* getOwner();
    Transform* getTransform() const;

    virtual void create();
    virtual void destroy();
    virtual void draw(SceneTree* tree) {}
    virtual void update(float delta);

    virtual void addToEngine(GameWindow* eng) {}

    void attachScript(Script* scr);

    static void RegisterObject(lua_State* L)
    {
        using namespace luabridge;
        getGlobalNamespace(L)
            .beginClass<Component>("Component")
            .addProperty("transform", &Component::getTransform)
            .addFunction("getowner", &Component::getOwner)
            .addFunction("setowner", &Component::setOwner)
            .endClass();
    }
private:
    Script* m_script;
    Node* m_owner;
};

#endif // COMPONENT_H
