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
#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>

#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering/win32/window_events.h>

#include <tov/rendering_gl/viewport.h>

#include <tov/rendering_gl/window_renderer_support.h>

using Viewport = tov::rendering::gl::Viewport;
using WindowPlatformSupport = tov::rendering::win32::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::win32::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem<Viewport>;

int main(int argc, char** argv)
{
	WindowPlatformSupport platformSupport;
	WindowRendererSupport rendererSupport;

	auto rs = RenderSystem(platformSupport, rendererSupport);
	tov::rendering::Camera c;

	/*auto window = rs.createRenderWindow("WINDWOWWW", 640, 480, false);
	auto vp1 = window->createViewport(c, 0, 0.0f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Red);
	auto vp2 = window->createViewport(c, 1, 0.5f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Green);*/

	auto window2 = rs.createRenderWindow("canvas2", 640, 180, false);
	auto vp3 = window2->createViewport(c, 2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Blue);

	while(1)
	{
		rs.renderFrame();
	}

#if TOV_COMPILER == TOV_COMPILER_MSVC
	system("PAUSE");
#endif

	return 0;
}
