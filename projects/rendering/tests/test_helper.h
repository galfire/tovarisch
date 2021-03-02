#ifndef TOV_RENDERING_TESTS_TEST_HELPER_H
#define TOV_RENDERING_TESTS_TEST_HELPER_H

#include <doctest.h>
#include <cstring>
#include <iostream>

#define SECTION(name) DOCTEST_SUBCASE(name)

#undef TEST_CASE
#define TEST_CASE(name, tags) DOCTEST_TEST_CASE(tags " " name)

inline bool cmpf(float a, float b, float epsilon = 9e-7)
{
	if (std::abs(a - b) < epsilon) return true;
	return false;
}

#endif
