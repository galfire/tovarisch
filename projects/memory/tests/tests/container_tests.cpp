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
        SECTION("emplaces new instances in order")
        {
            container.emplace_back(1);
            container.emplace_back(2);
            container.emplace_back(3);

            std::vector<Foo> v;
            std::ranges::copy(container, std::back_inserter(v));

            CHECK_EQ(v[0].i, 1);
            CHECK_EQ(v[1].i, 2);
            CHECK_EQ(v[2].i, 3);
        }
    }
}
