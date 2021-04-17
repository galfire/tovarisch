#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <iostream>

#include "application.h"

#include <tov/memory_config.h>
#include <tov/memory/container.h>

// ajkdfakld

using WindowPlatformSupport = tov::rendering::win32::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::win32::gl::WindowRendererSupport;

class Foo
{
public:
    Foo(int i)
        : m_i(i)
    {}

    ~Foo()
    {
        std::cout << "destryoing\n";
    }

public:
    int m_i;
};

int main(int argc, char** argv)
{
    WindowPlatformSupport platformSupport;
    WindowRendererSupport rendererSupport;

    Application application(
        "Window",
        platformSupport,
        rendererSupport
    );

    application.start();

    return 0;
}
