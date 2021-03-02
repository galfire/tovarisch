#include <doctest.h>
#include <cstring>

#define SECTION(name) DOCTEST_SUBCASE(name)

#undef TEST_CASE
#define TEST_CASE(name, tags) DOCTEST_TEST_CASE(tags " " name)

// catch exposes this by default outside of its namespace
using doctest::Approx;
