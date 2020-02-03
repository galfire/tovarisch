#include <iostream>

#include <array>
#include <vector>

#include <tov/core.h>
#include <tov/memory.h>

#include <tov/memory_config.h>

#include <tov/math/vector.h>

#include <tov/rendering/render_target.h>
#include <tov/rendering/camera.h>
#include <tov/rendering_gles/viewport.h>
#include <tov/rendering_gles/window_renderer_support.h>
#include <tov/rendering/platforms/win32/window_platform_support_win32.h>
#include <tov/rendering/platforms/win32/window_events.h>
#include <tov/rendering/render_window.h>

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
	//{
	//	auto obj = memory::ptr<MyDerivedObject>();
	//	auto obj2 = memory::ptr<MyDerivedObject>(123);
	//	auto obj3 = memory::ptr<MyDerivedObject>();
	//	std::cout << obj << "\n";
	//	std::cout << obj2 << "\n";
	//	std::cout << obj3 << "\n";
	//	std::cout << (uintptr_t)obj3 - (uintptr_t)obj2 << "\n";
	//	delete obj;
	//	delete obj2;
	//	delete obj3;
	//}

	////MyDerivedObject::reset();

	//auto objs = memory::ptr_array<MyDerivedObject, 3>();
	//std::cout << &objs[0] << "\n";
	//std::cout << &objs[1] << "\n";
	//std::cout << &objs[2] << "\n";
	//std::cout << (uintptr_t)&objs[0] % alignof(MyDerivedObject) << "\n";
	//std::cout << (uintptr_t)&objs[1] % alignof(MyDerivedObject) << "\n";
	//std::cout << (uintptr_t)&objs[2] % alignof(MyDerivedObject) << "\n";
	//std::cout << (uintptr_t)&objs[2] - (uintptr_t)&objs[1] << "\n";
	//delete[] objs;

	using Viewport = tov::rendering::gles::Viewport;

	/*tov::rendering::Camera c;
	tov::rendering::RenderTarget<Viewport> rt(1024, 100);
	auto v = rt.createViewport(c, 1, 0.5f);
	v->apply();*/

	const tov::rendering::gles::WindowRendererSupport rendererSupport;
	const tov::rendering::platforms::win32::WindowPlatformSupportWin32 platformSupport;
	tov::rendering::RenderWindow<Viewport> window(platformSupport, rendererSupport, 480, 480, false);

	tov::rendering::Camera c;
	auto vp = window.createViewport(c, 1);

	while(1)
	{
		tov::rendering::platforms::win32::WindowEvents::messageHandler();
		window.swapBuffers();
		vp->apply();

	}

#if TOV_COMPILER == TOV_COMPILER_MSVC
	system("PAUSE");
#endif

	return 0;
}
