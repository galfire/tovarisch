// player.cpp : Defines the entry point for the application.
//

#include <tov/rendering/web/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include "application.h"

#include <emscripten/emscripten.h>

using WindowPlatformSupport = tov::rendering::web::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::web::gl::WindowRendererSupport;

Application* application;

void oneIteration()
{
    application->call();
}

int main()
{
    WindowPlatformSupport platformSupport;
    WindowRendererSupport rendererSupport;

    application = new Application(
        "#canvas1",
        &platformSupport,
        &rendererSupport
    );
    
    emscripten_set_main_loop(oneIteration, 0, 1);

    return 0;
}
