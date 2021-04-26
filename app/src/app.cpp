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
    TOV_MOVABLE_ONLY(Foo);

public:
    Foo(int i)
        : m_i(i)
    {
        std::cout << "Creating " << this << "\n";
    }

    ~Foo()
    {
        std::cout << "Destryoing " << this << "\n";
    }

public:
    int m_i;
};

int main(int argc, char** argv)
{
    WindowPlatformSupport platformSupport;
    WindowRendererSupport rendererSupport;

    /*Application application(
        "Window",
        platformSupport,
        rendererSupport
    );

    application.start();*/

    {
        auto c = tov::memory::Container<Foo, 4>{};
        c.emplace_back(4);
        c.emplace_back(2);
        c.emplace_back(9);
        c.emplace_back(1);

        {
            auto& f = c[0];
            std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[1];
            std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[2];
            std::cout << f.m_i << "\n";
        }

        c.delete_at(0);
        c.emplace_back(2);

        std::cout << "\n\n\n";
        std::cout << "Destroying container...\n";
    }


    //auto c = container<int>{ 1, 3, 5 };
    //auto s = std::span{ c };

    return 0;
}
