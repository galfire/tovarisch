#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <iostream>
#include <ranges>

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
        std::cout << "Creating " << this << " (" << m_i << ")\n";
    }

    Foo(Foo&& f) noexcept
        : m_i(std::move(f.m_i))
    {
        std::cout << "Move creating " << this << " (" << m_i << ")\n";
    }

    Foo& operator = (Foo&& other) noexcept
    {
        std::cout << "Move assigning " << &other << " (" << other.m_i << ") to " << this << " (" << m_i << ")\n";
        m_i = std::move(other.m_i);
        return *this;
    }

    ~Foo()
    {
        std::cout << "Destryoing " << this << " (" << m_i << ")\n";
    }

public:
    int m_i;
};

int main(int argc, char** argv)
{
    //WindowPlatformSupport platformSupport;
    //WindowRendererSupport rendererSupport;

    //Application application(
    //    "Window",
    //    platformSupport,
    //    rendererSupport
    //);

    //application.start();

    {
        auto c = tov::memory::Container<Foo, 4>{};
        auto id_1 = c.emplace_back(1);
        auto id_2 = c.emplace_back(2);
        auto id_3 = c.emplace_back(3);
        auto id_4 = c.emplace_back(4);

        {
            auto& f = c[id_1];
            std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[id_2];
            std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[id_3];
            std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[id_4];
            std::cout << f.m_i << "\n";
        }

        c.delete_at(id_1);
        auto newid = c.emplace_back(5);

        {
            auto& f = c[id_1];
            //std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[id_2];
            std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[id_3];
            std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[id_4];
            std::cout << f.m_i << "\n";
        }

        {
            auto& f = c[newid];
            std::cout << f.m_i << "\n";
        }

        auto data = c.data();

        std::cout << "\n\n\n";
        std::cout << data[0].m_i << ", " << data[1].m_i << ", " << data[2].m_i << ", " << data[3].m_i << "\n";

        std::cout << "\n\n\n";


        //std::iter_difference_t<tov::memory::Container<Foo, 4>>;
        //auto b = std::ranges::begin(c);
        //std::cout << "b: " << b << "\n";
        


        for (auto&& n : c) {
            std::cout << "N: " << n.m_i << std::endl;
        }

        //std::cout << std::extent<tov::memory::Container<Foo, 4>>::value << "\n";
        //std::cout << "SIZE: " << std::ranges::size(c) << "\n";
        //std::cout << "DIST: " << std::ranges::distance(c.begin(), c.end()) << "\n";

        auto s = std::span{ c };
        for (auto&& n : s) {
            std::cout << "S: " << n.m_i << std::endl;
        }

        std::cout << "Destroying container...\n";
    }


    return 0;
}
