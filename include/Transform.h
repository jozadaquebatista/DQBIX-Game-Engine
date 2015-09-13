// File: Transform.h
// Class: Transform
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_TRANSFORM__
#define __NIX_TRANSFORM__
#pragma once

#include "graphics.h"
#include "Dummies.h"
#include "lua.hpp"

class Transform
{

public:
	Transform();

    Vector3 getTranslation() const
	{
		Vector3 ret;
		ret.x = m_translation.x;
		ret.y = m_translation.y;
		ret.z = m_translation.z;
		return ret;
	}
	Vector3 getScale()
	{ 
		Vector3 ret;
		ret.x = m_scale.x;
		ret.y = m_scale.y;
		ret.z = m_scale.z;
		return ret;
	}
	Vector3 getRotation()
	{
		vec3 rot = eulerAngles(m_rotation);
		Vector3 ret;
		ret.x = rot.x;
		ret.y = rot.y;
		ret.z = rot.z;
		return ret;
	}

	void setTranslation(Vector3 v) { m_translation = vec3(v.x, v.y, v.z); }
	void setScale(Vector3 v) { m_scale = vec3(v.x, v.y, v.z); }
	void setRotation(float a, Vector3 v)
	{ 
		m_rotation = rotate(quat(1.0f, 0.0f, 0.0f, 0.0f), a, vec3(v.x, v.y, v.z));
	}
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
	void scale_transform(float x, float y, float z);

	mat4 getTransformation();
	mat4 getParentMatrix();

	bool changed();
	void update();

	static void RegisterObject(lua_State* L)
	{
		RegisterDummyObjects(L);

		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<Transform>("Transform")
			.addConstructor<void(*)(void)>()
			.addProperty("parent", &Transform::getParent, &Transform::setParent)
			.addFunction("rotate", &Transform::rotate_transform)
			.addFunction("scale", &Transform::scale_transform)
			.addFunction("move", &Transform::move)
            .addFunction("getposition", &Transform::getTranslation)
            .addFunction("setposition", &Transform::setTranslation)
			.addFunction("getscale", &Transform::getScale)
			.addFunction("setscale", &Transform::setScale)
			.addFunction("getrotation", &Transform::getRotation)
			.addFunction("setrotation", &Transform::setRotation)
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
