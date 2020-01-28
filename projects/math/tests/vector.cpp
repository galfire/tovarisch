#include <catch2/catch.hpp>

#include <tov/math/vector.h>

TEST_CASE("Vector2", "[Vector2]")
{
	SECTION("constructor")
	{
		SECTION("accepts arguments for x and y")
		{
			tov::math::Vector2 vec(1.0f, 1.0f);
			REQUIRE(vec.x == 1.0f);
			REQUIRE(vec.y == 1.0f);
		}
	}

	SECTION("subscript")
	{
		SECTION("returns the vector element at the given index")
		{
			tov::math::Vector2 vec(2.0f, 3.0f);
			REQUIRE(vec[0] == 2.0f);
			REQUIRE(vec[1] == 3.0f);
		}
	}

	SECTION("vector addition")
	{
		SECTION("returns the sum of the LHS and RHS vectors")
		{
			tov::math::Vector2 vec1(1.0f, 1.0f);
			tov::math::Vector2 vec2(1.0f, 1.0f);
			tov::math::Vector2 vecSum = vec1 + vec2;
			REQUIRE(vecSum.x == 2.0f);
			REQUIRE(vecSum.y == 2.0f);
		}
	}


	SECTION("vector addition assignment")
	{
		SECTION("sets the LHS vector to the sum of the LHS and RHS vectors")
		{
			tov::math::Vector2 vec1(1.0f, 1.0f);
			tov::math::Vector2 vec2(1.0f, 1.0f);
			vec1 += vec2;
			REQUIRE(vec1[0] == 2.0f);
			REQUIRE(vec1[1] == 2.0f);
		}
	}

	SECTION("vector subtraction")
	{
		SECTION("returns the difference of the LHS and RHS vectors")
		{
			tov::math::Vector2 vec1(1.0f, 1.0f);
			tov::math::Vector2 vec2(1.0f, 1.0f);
			tov::math::Vector2 vecDiff = vec1 - vec2;
			REQUIRE(vecDiff.x == 0.0f);
			REQUIRE(vecDiff.y == 0.0f);
		}
	}

	SECTION("vector subtraction assignment")
	{
		SECTION("sets the LHS vector to the difference of the LHS and RHS vectors")
		{
			tov::math::Vector2 vec1(1.0f, 1.0f);
			tov::math::Vector2 vec2(1.0f, 1.0f);
			vec1 -= vec2;
			REQUIRE(vec1[0] == 0.0f);
			REQUIRE(vec1[1] == 0.0f);
		}
	}
}

TEST_CASE("Vector3", "[Vector3]")
{
	SECTION("constructor")
	{
		SECTION("accepts arguments for x, y, and z")
		{
			tov::math::Vector3 vec(1.0f, 1.0f, 1.0f);
			REQUIRE(vec.x == 1.0f);
			REQUIRE(vec.y == 1.0f);
			REQUIRE(vec.z == 1.0f);
		}
	}

	SECTION("subscript")
	{
		SECTION("returns the vector element at the given index")
		{
			tov::math::Vector3 vec(2.0f, 3.0f, 4.0f);
			REQUIRE(vec[0] == 2.0f);
			REQUIRE(vec[1] == 3.0f);
			REQUIRE(vec[2] == 4.0f);
		}
	}

	SECTION("vector addition")
	{
		SECTION("returns the sum of the LHS and RHS vectors")
		{
			tov::math::Vector3 vec1(1.0f, 1.0f, 1.0f);
			tov::math::Vector3 vec2(1.0f, 1.0f, 1.0f);
			tov::math::Vector3 vecSum = vec1 + vec2;
			REQUIRE(vecSum.x == 2.0f);
			REQUIRE(vecSum.y == 2.0f);
			REQUIRE(vecSum.z == 2.0f);
		}
	}

	SECTION("vector addition assignment")
	{
		SECTION("sets the LHS vector to the sum of the LHS and RHS vectors")
		{
			tov::math::Vector3 vec1(1.0f, 1.0f, 1.0f);
			tov::math::Vector3 vec2(1.0f, 1.0f, 1.0f);
			vec1 += vec2;
			REQUIRE(vec1[0] == 2.0f);
			REQUIRE(vec1[1] == 2.0f);
			REQUIRE(vec1[2] == 2.0f);
		}
	}

	SECTION("vector subtraction")
	{
		SECTION("returns the difference of the LHS and RHS vectors")
		{
			tov::math::Vector3 vec1(1.0f, 1.0f, 1.0f);
			tov::math::Vector3 vec2(1.0f, 1.0f, 1.0f);
			tov::math::Vector3 vecDiff = vec1 - vec2;
			REQUIRE(vecDiff.x == 0.0f);
			REQUIRE(vecDiff.y == 0.0f);
			REQUIRE(vecDiff.z == 0.0f);
		}
	}

	SECTION("vector subtraction assignment")
	{
		SECTION("sets the LHS vector to the difference of the LHS and RHS vectors")
		{
			tov::math::Vector3 vec1(1.0f, 1.0f, 1.0f);
			tov::math::Vector3 vec2(1.0f, 1.0f, 1.0f);
			vec1 -= vec2;
			REQUIRE(vec1[0] == 0.0f);
			REQUIRE(vec1[1] == 0.0f);
			REQUIRE(vec1[2] == 0.0f);
		}
	}

	SECTION("crossProduct")
	{
		SECTION("returns the cross product of the LHS and RHS vectors")
		{
			tov::math::Vector3 vec1(1.0f, 2.0f, 3.0f);
			tov::math::Vector3 vec2(2.0f, 3.0f, 4.0f);
			tov::math::Vector3 vecCrossProduct = vec1.crossProduct(vec2);
			REQUIRE(vecCrossProduct.x == -1.0f);
			REQUIRE(vecCrossProduct.y == 2.0f);
			REQUIRE(vecCrossProduct.z == -1.0f);
		}

		SECTION("can be called using the * operator")
		{
			tov::math::Vector3 vec1(1.0f, 2.0f, 3.0f);
			tov::math::Vector3 vec2(2.0f, 3.0f, 4.0f);
			tov::math::Vector3 vecCrossProduct = vec1 * vec2;
			REQUIRE(vecCrossProduct.x == -1.0f);
			REQUIRE(vecCrossProduct.y == 2.0f);
			REQUIRE(vecCrossProduct.z == -1.0f);
		}
	}
}

TEST_CASE("Vector", "[Vector]")
{
	SECTION("constructor")
	{
		SECTION("accepts arguments for each element")
		{
			tov::math::Vector<5> vec(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
			REQUIRE(vec[0] == 1.0f);
			REQUIRE(vec[1] == 2.0f);
			REQUIRE(vec[2] == 3.0f);
			REQUIRE(vec[3] == 4.0f);
			REQUIRE(vec[4] == 5.0f);
		}
	}

	SECTION("subscript")
	{
		SECTION("returns the vector element at the given index")
		{
			tov::math::Vector<5> vec(1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
			REQUIRE(vec[0] == 1.0f);
			REQUIRE(vec[1] == 2.0f);
			REQUIRE(vec[2] == 3.0f);
			REQUIRE(vec[3] == 4.0f);
			REQUIRE(vec[4] == 5.0f);
		}
	}

	SECTION("vector addition")
	{
		SECTION("returns the sum of the LHS and RHS vectors")
		{
			tov::math::Vector<5> vec1(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
			tov::math::Vector<5> vec2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
			tov::math::Vector<5> vecSum = vec1 + vec2;
			REQUIRE(vecSum[0] == 2.0f);
			REQUIRE(vecSum[1] == 2.0f);
			REQUIRE(vecSum[2] == 2.0f);
			REQUIRE(vecSum[3] == 2.0f);
			REQUIRE(vecSum[4] == 2.0f);
		}
	}

	SECTION("vector subtraction")
	{
		SECTION("returns the difference of the LHS and RHS vectors")
		{
			tov::math::Vector<5> vec1(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
			tov::math::Vector<5> vec2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
			tov::math::Vector<5> vecDiff = vec1 - vec2;
			REQUIRE(vecDiff[0] == 0.0f);
			REQUIRE(vecDiff[1] == 0.0f);
			REQUIRE(vecDiff[2] == 0.0f);
			REQUIRE(vecDiff[3] == 0.0f);
			REQUIRE(vecDiff[4] == 0.0f);
		}
	}
}
