// player.cpp : Defines the entry point for the application.
//

#include "player.h"

#include <tov/core.h>

#include <tov/rendering/render_target.h>
#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>

#include <tov/rendering/web/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <tov/rendering_gl/viewport.h>

#include <emscripten/emscripten.h>

using Viewport = tov::rendering::gl::Viewport;
using WindowPlatformSupport = tov::rendering::web::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::web::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem<Viewport>;

RenderSystem* rs;

void oneIteration()
{
	rs->renderFrame();
}

int main()
{
	WindowPlatformSupport platformSupport;
	WindowRendererSupport rendererSupport;

	rs = new RenderSystem(platformSupport, rendererSupport);
	tov::rendering::Camera c;
	
	auto window = rs->createRenderWindow("canvas", 640, 480, false);
	auto vp1 = window->createViewport(c, 0, 0.0f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Red);
	auto vp2 = window->createViewport(c, 1, 0.5f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Green);

	auto window2 = rs->createRenderWindow("canvas2", 640, 180, false);
	auto vp3 = window2->createViewport(c, 2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Blue);

	emscripten_set_main_loop(oneIteration, 30, 1);

	return 0;
}
