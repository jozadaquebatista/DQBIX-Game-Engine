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
#include <vector>

class Node
{
public:
	Node();
	virtual ~Node();

	Node* addChild(Node* obj);
	Transform* getTransform() const { return m_transform; }

	void drawAll();
	virtual void draw() {}
private:
	Transform* m_transform;
	std::vector<Node*> m_children;
	
	void updateAll();
	void update();
};

#endif //__NIX_NODE__