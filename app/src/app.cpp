#include <iostream>

#include <array>
#include <vector>

#include <tov/core.h>
#include <tov/memory.h>

#include <tov/memory_config.h>

#include <tov/math/vector.h>

#include <tov/rendering/render_target.h>
#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/render_window.h>

#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering/win32/window_events.h>

#include <tov/rendering_gl/viewport.h>

#include <tov/rendering_gl/window_renderer_support.h>


using namespace tov;

int main(int argc, char** argv)
{
	using Viewport = tov::rendering::gl::Viewport;

	const tov::rendering::win32::gl::WindowRendererSupport rendererSupport;
	const tov::rendering::win32::WindowPlatformSupport platformSupport;
	tov::rendering::RenderWindow<Viewport> window(platformSupport, rendererSupport, 480, 480, false);

	tov::rendering::Camera c;
	auto vp1 = window.createViewport(c, 0, 0.0f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Red);
	auto vp2 = window.createViewport(c, 1, 0.5f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Green);

	while(1)
	{
		tov::rendering::win32::WindowEvents::messageHandler();
		window.swapBuffers();
		vp1->apply();
		vp2->apply();
	}

#if TOV_COMPILER == TOV_COMPILER_MSVC
	system("PAUSE");
#endif

	return 0;
}
