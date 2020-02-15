#include "test_helper.h"

#include <tov/math/matrix.h>

#include <iostream>

TEST_CASE("Matrix", "[Matrix]")
{
	using Matrix = tov::math::Matrix<float, 3, 3, tov::math::SIMD::_128F>;

	SECTION("element constructor")
	{
		SECTION("accepts M * N elements")
		{
			Matrix m(
				1.f, 2.f, 3.f,
				1.f, 2.f, 3.f,
				1.f, 2.f, 3.f
			);

			REQUIRE(m[0][0] == 1.0f);
			REQUIRE(m[0][1] == 2.0f);
			REQUIRE(m[0][2] == 3.0f);
			REQUIRE(m[1][0] == 1.0f);
			REQUIRE(m[1][1] == 2.0f);
			REQUIRE(m[1][2] == 3.0f);
			REQUIRE(m[2][0] == 1.0f);
			REQUIRE(m[2][1] == 2.0f);
			REQUIRE(m[2][2] == 3.0f);
		}
	}

	SECTION("transpose")
	{
		SECTION("returns the transpose of the matrix")
		{
			Matrix m(
				1.f, 2.f, 3.f,
				1.f, 2.f, 3.f,
				1.f, 2.f, 3.f
			);

			Matrix mT = m.transpose();

			REQUIRE(mT[0][0] == 1.0f);
			REQUIRE(mT[0][1] == 1.0f);
			REQUIRE(mT[0][2] == 1.0f);
			REQUIRE(mT[1][0] == 2.0f);
			REQUIRE(mT[1][1] == 2.0f);
			REQUIRE(mT[1][2] == 2.0f);
			REQUIRE(mT[2][0] == 3.0f);
			REQUIRE(mT[2][1] == 3.0f);
			REQUIRE(mT[2][2] == 3.0f);
		}
		
	}

	SECTION("concatenate")
	{
		SECTION("returns the concatenation of the matrix and the given matrix")
		{
			Matrix m(
				1.f, 2.f, 3.f,
				1.f, 2.f, 3.f,
				1.f, 2.f, 3.f
			);

			Matrix mC = m.concatenate(m);

			REQUIRE(mC[0][0] == 6.0f);
			REQUIRE(mC[0][1] == 12.0f);
			REQUIRE(mC[0][2] == 18.0f);
			REQUIRE(mC[1][0] == 6.0f);
			REQUIRE(mC[1][1] == 12.0f);
			REQUIRE(mC[1][2] == 18.0f);
			REQUIRE(mC[2][0] == 6.0f);
			REQUIRE(mC[2][1] == 12.0f);
			REQUIRE(mC[2][2] == 18.0f);
		}
	}
}
