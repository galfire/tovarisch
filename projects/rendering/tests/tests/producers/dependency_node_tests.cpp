#include "test_helper.h"

#include <tov/rendering/producers/dependency_node.h>

class Foo
    : public tov::rendering::producers::DependencyNode
{};

TEST_CASE("DependencyNode", "[DependencyNode]")
{
    SECTION("thing")
    {
        Foo d0, d1, d2, d3, d4;

        /*
        *       d0
        *       | \
        *       d1 |
        *      /  \|
        *    d2    d3
        *      \  /
        *       d4
        * 
        * d4: d0, d1, d2, d3, d4
        */

        d4.addDependency(&d2);
        d4.addDependency(&d3);
        d2.addDependency(&d1);
        d3.addDependency(&d1);
        d3.addDependency(&d0);
        d1.addDependency(&d0);
        d4.addDependency(&d1);

        auto resolved = d4.getResolvedDependencies();

        CHECK(resolved.size() == 5);

        CHECK(resolved[0] == &d0);
        CHECK(resolved[1] == &d1);
        CHECK(resolved[2] == &d2);
        CHECK(resolved[3] == &d3);
        CHECK(resolved[4] == &d4);
    }
}