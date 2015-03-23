#include "..\include\SceneTree.h"


SceneTree::SceneTree() : m_root(0)
{
}


SceneTree::~SceneTree()
{
    SAFE_DELETE(m_root);
}

void SceneTree::create()
{
    m_root->createAll();
}

void SceneTree::render()
{
	m_root->drawAll();
}

void SceneTree::update(float delta)
{
    m_root->updateAll(delta);
}

void SceneTree::RegisterObject(lua_State *L)
{
    using namespace luabridge;
    getGlobalNamespace(L)
            .beginClass<SceneTree>("SceneTree")
            .addFunction("getRoot", &SceneTree::getRootNode)
            .addFunction("addChild", &SceneTree::addChild)
            .endClass();
}
