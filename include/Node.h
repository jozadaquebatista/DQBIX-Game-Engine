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
	~Node();

	Node* addChild(Node* obj);
	Transform* getTransform() const { return m_transform; }

	void drawAll();
	virtual void draw() {}
	virtual void update(float delta);

	void updateAll(float delta);

	void setName(std::string newname);
	std::string getName() const { return name; }

	Node* getNode(std::string name);

	Node* getParentNode() const { return m_parentnode; }
	void setParentNode(Node* n) { m_parentnode = n; }
private:
	Node* m_parentnode;
	Transform* m_transform;
	std::vector<Node*> m_children;
	std::string name;	
};

#endif //__NIX_NODE__