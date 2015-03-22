// THIS FILE IS PART OF THE NEW ENGINE PROJECT
// IF YOU WANT TO USE THE OLD ENGINE, YOU NEED TO
// DEFINE OLD_ENGINE ON main.cpp
// ===============================================
// File: Transform.h
// Class: Transform
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_TRANSFORM__
#define __NIX_TRANSFORM__
#pragma once

#include "graphics.h"
#include "lua.hpp"

class Transform
{
public:
	Transform();

	vec3 getTranslation()
	{
		return m_translation;
	}
	vec3 getScale()
	{ 
		return m_scale;
	}
	quat getRotation()
	{
		return m_rotation;
	}

	void setTranslation(float x, float y, float z) { m_translation = vec3(x, y, z); }
	void setScale(float x, float y, float z) { m_scale = vec3(x, y, z); }
	void setRotation(float x, float y, float z, float w) { m_rotation = quat(w, x, y, z); }
	Transform* getParent() const { return m_parent; }
	void setParent(Transform* p) { m_parent = p; }

	inline vec3 getTransformedTranslation()
	{
		vec4 p = vec4(1.0f) * translate(getParentMatrix(), m_translation);
		return vec3(p.x, p.y, p.z);
	}
	inline quat getTransformedRotation()
	{
		quat pRot = quat(1.0f, 0.0f, 0.0f, 0.0f);
		if (m_parent)
			pRot = m_parent->getTransformedRotation();
		return pRot * m_rotation;
	}

	void rotate_transform(float x, float y, float z);
	void move(float x, float y, float z);

	mat4 getTransformation();
	mat4 getParentMatrix();

	bool changed();
	void update();

	static void RegisterObject(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<Transform>("Transform")
			.addConstructor<void(*)(void)>()
			.addProperty("parent", &Transform::getParent, &Transform::setParent)
			.addFunction("rotate", &Transform::rotate_transform)
			.addFunction("scale", &Transform::setScale)
			.addFunction("move", &Transform::move)
			.endClass();
	}
private:
	mat4 m_parentMat;
	vec3 m_translation;
	vec3 m_scale;
	quat m_rotation;
	vec3 m_oldTranslation;
	vec3 m_oldScale;
	quat m_oldRotation;
	Transform* m_parent;
	bool m_initOld;
};

#endif //__NIX_TRANSFORM__