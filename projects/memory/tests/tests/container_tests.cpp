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

        SECTION("increases the size")
        {
            container.emplace_back(1);
            container.emplace_back(2);
            container.emplace_back(3);

            CHECK_EQ(container.size(), 3);
        }
    }

    SECTION("erase")
    {
        SECTION("defragments the container")
        {
            auto i1 = container.emplace_back(1);
            auto i2 = container.emplace_back(2);
            auto i3 = container.emplace_back(3);

            container.erase(i2);

            std::vector<Foo> v;
            std::ranges::copy(container, std::back_inserter(v));

            CHECK_EQ(v[0].i, 1);
            CHECK_EQ(v[1].i, 3);
        }

        SECTION("reduces the size")
        {
            auto i1 = container.emplace_back(1);
            auto i2 = container.emplace_back(2);
            auto i3 = container.emplace_back(3);

            container.erase(i2);

            CHECK_EQ(container.size(), 2);
        }
    }

    SECTION("begin")
    {
        SECTION("returns an iterator to the start of the container")
        {
            auto i1 = container.emplace_back(1);
            auto i2 = container.emplace_back(2);
            auto i3 = container.emplace_back(3);

            auto it = container.begin();

            CHECK_EQ((*it).i, 1);
        }
    }

    SECTION("prevents fragmentation by reordering elements")
    {
        auto i1 = container.emplace_back(1);
        auto i2 = container.emplace_back(2);
        auto i3 = container.emplace_back(3);

        // Erase the element at i1, and move the last element (at i3) in its place
        container.erase(i1);

        auto i4 = container.emplace_back(4);

        std::vector<Foo> v;
        std::ranges::copy(container, std::back_inserter(v));

        CHECK_EQ(v[0].i, 3);
        CHECK_EQ(v[1].i, 2);
        CHECK_EQ(v[2].i, 4);
    }

    SECTION("converts to a span")
    {
        container.emplace_back(1);
        container.emplace_back(2);
        container.emplace_back(3);

        auto span = std::span{ container };

        std::vector<Foo> v;
        std::ranges::copy(span, std::back_inserter(v));

        CHECK_EQ(v[0].i, 1);
        CHECK_EQ(v[1].i, 2);
        CHECK_EQ(v[2].i, 3);
    }
}
