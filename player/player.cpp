// player.cpp : Defines the entry point for the application.
//

#include "player.h"

#include <tov/core.h>
#include <tov/memory/heap_area.h>
#include <tov/memory.h>

#include <tov/memory_config.h>

#include <tov/math/vector.h>

class MyObject
	: public tov::memory::AllocatedObjectLinear
{
public:
	MyObject() = default;
	virtual ~MyObject() = default;
};

class MyDerivedObject
	: public MyObject
{
public:
	MyDerivedObject() = default;
	MyDerivedObject(size_t i) {};
	~MyDerivedObject() = default;
};

int main()
{
	/*{
		auto obj = tov::memory::ptr<MyDerivedObject>();
		auto obj2 = tov::memory::ptr<MyDerivedObject>(123);
		auto obj3 = tov::memory::ptr<MyDerivedObject>();
		std::cout << obj << "\n";
		std::cout << obj2 << "\n";
		std::cout << obj3 << "\n";
		std::cout << (uintptr_t)obj3 - (uintptr_t)obj2 << "\n";
		delete obj;
		delete obj2;
		delete obj3;
	}

	auto objs = tov::memory::ptr_array<MyDerivedObject, 3>();
	std::cout << &objs[0] << "\n";
	std::cout << &objs[1] << "\n";
	std::cout << &objs[2] << "\n";
	std::cout << (uintptr_t)&objs[0] % alignof(MyDerivedObject) << "\n";
	std::cout << (uintptr_t)&objs[1] % alignof(MyDerivedObject) << "\n";
	std::cout << (uintptr_t)&objs[2] % alignof(MyDerivedObject) << "\n";
	std::cout << (uintptr_t)&objs[2] - (uintptr_t)&objs[1] << "\n";
	delete[] objs;*/

	tov::math::Vector3 v1(1.0f, 2.0f, 3.0f);
	tov::math::Vector3 v2(2.0f, 3.0f, 4.0f);
	auto&& v3 = v1.cross(v2);

	std::cout << v3 << "\n";

	return 0;
}
