// File: SceneTree.h
// Class: SceneTree
// Author: Diego Lopes <diego95lopes@live.com>
// 21/03/2015
#ifndef __NIX_SCENETREE__
#define __NIX_SCENETREE__
#pragma once

#include "Node.h"
class SceneTree
{
public:
	SceneTree();
	virtual ~SceneTree();

	Node* getRootNode()
	{ 
        if (m_root == NULL)
        {
			m_root = new Node();
            m_root->setName("__root__");
        }
		return m_root; 
	}

    void create();
	void render();
	void update(float delta);

    Node* addChild(Node* n)
    {
		return getRootNode()->addChild(n);
	}

    static void RegisterObject(lua_State* L);
private:
    SceneTree(SceneTree&) {}
	void operator=(SceneTree s) {}
	Node* m_root;
};

#endif // __NIX_SCENETREE__
