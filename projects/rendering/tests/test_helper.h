#ifndef TOV_RENDERING_TESTS_TEST_HELPER_H
#define TOV_RENDERING_TESTS_TEST_HELPER_H

#include <catch2/catch.hpp>

#include <iostream>

inline bool cmpf(float a, float b, float epsilon = 9e-7)
{
	if (std::abs(a - b) < epsilon) return true;
	return false;
}

#endif
