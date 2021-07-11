#include "test_helper.h"

#include <tov/memory/container.h>

#include <span>

TEST_CASE("Container", "[Container]")
{
    class Foo
    {
    public:
        Foo(int i)
            : i(i)
        {}

        ~Foo() {}

    public:
        int i;
    };

    auto container = tov::memory::Container<Foo, 4>();

    SECTION("emplace_back")
    {
        auto a = container.emplace_back(1);
        auto b = container.emplace_back(2);
        auto c = container.emplace_back(3);
        auto d = container.emplace_back(4);

        auto s = std::span{ container };
        for (auto&& i : s)
        {
            std::cout << i.i << "\n";
        }
    }
}
