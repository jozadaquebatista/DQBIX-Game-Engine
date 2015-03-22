#include "../include/Dummies.h"

void RegisterDummyObjects(lua_State* L)
{
	using namespace luabridge;

	getGlobalNamespace(L)
		.beginClass<Vector2>("Vector2")
		.addConstructor<void(*)(float, float)>()
		.addData("x", &Vector2::x)
		.addData("y", &Vector2::y)
		.addFunction("length", &Vector2::length)
		.endClass()
		.beginClass<Vector3>("Vector3")
		.addConstructor<void(*)(float, float, float)>()
		.addData("x", &Vector3::x)
		.addData("y", &Vector3::y)
		.addData("z", &Vector3::z)
		.addFunction("length", &Vector3::length)
		.endClass()
		.beginClass<Quaternion>("Quaternion")
		.addConstructor<void(*)(float, float, float, float)>()
		.addData("x", &Quaternion::x)
		.addData("y", &Quaternion::y)
		.addData("z", &Quaternion::z)
		.addData("w", &Quaternion::w)
		.addFunction("length", &Quaternion::length)
		.endClass();
}
