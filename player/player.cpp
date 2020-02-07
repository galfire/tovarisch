// player.cpp : Defines the entry point for the application.
//

#include "player.h"

#include <tov/core.h>

#include <tov/rendering/render_target.h>
#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/render_window.h>

#include <tov/rendering/web/window_platform_support.h>

#include <tov/rendering_gl/viewport.h>

#include <tov/rendering_gl/window_renderer_support.h>

#include <emscripten/emscripten.h>

using Viewport = tov::rendering::gl::Viewport;

const tov::rendering::web::gl::WindowRendererSupport rendererSupport;
const tov::rendering::web::WindowPlatformSupport platformSupport;
tov::rendering::RenderWindow<Viewport> window(platformSupport, rendererSupport, 480, 480, false);

tov::rendering::Camera c;
tov::rendering::Viewport<Viewport>* vp1;
tov::rendering::Viewport<Viewport>* vp2;

void oneIteration()
{
	window.swapBuffers();
	vp1->apply();
	vp2->apply();
	//emscripten_webgl_commit_frame();
}

int main()
{
	vp1 = window.createViewport(c, 0, 0.0f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Red);
	vp2 = window.createViewport(c, 1, 0.5f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Green);

	emscripten_set_main_loop(oneIteration, 30, 1);

	return 0;
}
