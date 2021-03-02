#ifndef TOV_MATH_TESTS_TEST_HELPER_H
#define TOV_MATH_TESTS_TEST_HELPER_H

#include <doctest.h>
#include <cmath>

#define SECTION(name) DOCTEST_SUBCASE(name)

#undef TEST_CASE
#define TEST_CASE(name, tags) DOCTEST_TEST_CASE(tags " " name)

// catch exposes this by default outside of its namespace
using doctest::Approx;


inline bool cmpf(float a, float b, float epsilon = 1e-7)
{
    if (std::abs(a - b) < epsilon) return true;
    return false;
}

#include <cstring>

#endif
