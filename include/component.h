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

    Vector3 getOffset() const { return m_offset; }
    void setOffset(Vector3 of) { m_offset = of; }

    virtual void create() {}
    virtual void destroy() {}
    virtual void update(float delta) {}
    virtual void draw(SceneTree* tree) {}    

    virtual void addToEngine(GameWindow* eng) {}

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
    Node* m_owner;
    Vector3 m_offset;
};

#endif // COMPONENT_H
