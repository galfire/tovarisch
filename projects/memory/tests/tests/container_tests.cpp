#include "test_helper.h"

#include <tov/memory/container.h>

TEST_CASE("Container", "[Container]")
{
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

    auto container = tov::memory::Container<Foo, 4>();

    SECTION("create")
    {
        auto a = container.emplace_back(1);
        auto b = container.emplace_back(2);
        auto c = container.emplace_back(3);
        auto d = container.emplace_back(4);
        //std::cout << a.m_i << "\n";
    }

    //SECTION("create")
    //{
    //    //auto i = std::ranges::size(container);
    //    //std::cout << i << "\n";
    //}

}
