#include "..\include\SceneTree.h"


SceneTree::SceneTree() : m_root(0)
{
}


SceneTree::~SceneTree()
{
	SAFE_DELETE(m_root);
}

void SceneTree::render()
{
	m_root->drawAll();
}

void SceneTree::update(float delta)
{
	m_root->updateAll(delta);
}
