// For Lua binding (since I can't bind the GLM::vec2 and GLM::vec3)
// File: Dummies.h
// Class: Dummies
// Author: Diego Lopes <diego95lopes@live.com>
// 22/03/2015
#ifndef __NIX_DUMMY__
#define __NIX_DUMMY__
#pragma once

#include <cmath>
#include "lua.hpp"

void RegisterDummyObjects(lua_State* L);

typedef struct Vector3
{
	float x, y, z;
	float length()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	Vector3() {}
	Vector3(float vx, float vy, float vz)
		: x(vx), y(vy), z(vz)
	{

	}
} Vector3;

typedef struct Vector2
{
	float x, y;
	float length()
	{
		return sqrtf(x * x + y * y);
	}
	Vector2() {}
	Vector2(float vx, float vy)
		: x(vx), y(vy)
	{

	}
} Vector2;

typedef struct Quaternion
{
	float x, y, z, w;
	float length()
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}
	Quaternion() {}
	Quaternion(float vx, float vy, float vz, float vw)
		: x(vx), y(vy), z(vz), w(vw)
	{

	}
} Quaternion;

#endif // __NIX_DUMMY__