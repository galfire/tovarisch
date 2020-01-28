#include <iostream>

#include <array>
#include <vector>

#include <tov/core.h>
#include <tov/memory.h>

#include <tov/memory_config.h>

#include <tov/math/vector.h>

using namespace tov;

class MyObject
	: public tov::memory::AllocatedObjectLinear
{
public:
	MyObject() = default;
	virtual ~MyObject() = default;
};

class alignas(32) MyDerivedObject
	: public MyObject
{
public:
	MyDerivedObject() = default;
	MyDerivedObject(size_t i) {}
	~MyDerivedObject() = default;
};

int main(int argc, char** argv)
{
	{
		auto obj = memory::ptr<MyDerivedObject>();
		auto obj2 = memory::ptr<MyDerivedObject>(123);
		auto obj3 = memory::ptr<MyDerivedObject>();
		std::cout << obj << "\n";
		std::cout << obj2 << "\n";
		std::cout << obj3 << "\n";
		std::cout << (uintptr_t)obj3 - (uintptr_t)obj2 << "\n";
		delete obj;
		delete obj2;
		delete obj3;
	}

	//MyDerivedObject::reset();

	auto objs = memory::ptr_array<MyDerivedObject, 3>();
	std::cout << &objs[0] << "\n";
	std::cout << &objs[1] << "\n";
	std::cout << &objs[2] << "\n";
	std::cout << (uintptr_t)&objs[0] % alignof(MyDerivedObject) << "\n";
	std::cout << (uintptr_t)&objs[1] % alignof(MyDerivedObject) << "\n";
	std::cout << (uintptr_t)&objs[2] % alignof(MyDerivedObject) << "\n";
	std::cout << (uintptr_t)&objs[2] - (uintptr_t)&objs[1] << "\n";
	delete[] objs;

	tov::math::Vector<5> vec1(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	tov::math::Vector<5> vec2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	//auto vecSum = vec1 + vec2;
	tov::math::Vector<5>&& vecSum = vec1 + vec2;

	std::cout << "Vec1: " << &vec1 << "\n";
	std::cout << "Vec2: " << &vec2 << "\n";
	std::cout << "VecSum: " << &vecSum << "\n";
	std::cout << vecSum << "\n";


#if TOV_COMPILER == TOV_COMPILER_MSVC
	system("PAUSE");
#endif

	return 0;
}
