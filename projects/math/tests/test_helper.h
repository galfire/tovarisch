#ifndef TOV_MATH_TESTS_TEST_HELPER_H
#define TOV_MATH_TESTS_TEST_HELPER_H

#include <catch2/catch.hpp>

inline bool cmpf(float a, float b, float epsilon = 1e-7)
{
    if (std::abs(a - b) < epsilon) return true;
    return false;
}

#endif
