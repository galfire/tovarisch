#include <doctest.h>
#include <cstring>

#define SECTION(name) DOCTEST_SUBCASE(name)

#undef TEST_CASE
#define TEST_CASE(name, tags) DOCTEST_TEST_CASE(tags " " name)

using doctest::Approx;
