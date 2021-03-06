#include "test_helper.h"

#include <tov/math/vector.h>

TEST_CASE("Vector SIMD None", "[Vector]")
{
    using Vector3 = tov::math::Vector<3, tov::math::SIMD::_NONE>;

    SECTION("element constructor")
    {
        SECTION("accepts arguments for each element")
        {
            Vector3 vec(1.0f, 2.0f, 3.0f);
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 2.0f);
            CHECK(vec[2] == 3.0f);
        }
    }

    SECTION("copy constructor")
    {
        SECTION("accepts a Vector argument")
        {
            Vector3 vecArg(1.0f, 1.0f, 1.0f);
            Vector3 vec(vecArg);
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 1.0f);
            CHECK(vec[2] == 1.0f);
        }
    }

    SECTION("assignment")
    {
        SECTION("sets the LHS vector to the RHS vector")
        {
            Vector3 vecArg(1.0f, 1.0f, 1.0f);
            Vector3 vec = vecArg;
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 1.0f);
            CHECK(vec[2] == 1.0f);
        }
    }

    SECTION("subscript")
    {
        SECTION("returns the vector element at the given index")
        {
            Vector3 vec(1.0f, 2.0f, 3.0f);
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 2.0f);
            CHECK(vec[2] == 3.0f);
        }
    }

    SECTION("unary plus")
    {
        SECTION("returns the RHS vector")
        {
            Vector3 vecArg(1.0f, 2.0f, 3.0f);
            Vector3 vec = +vecArg;
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 2.0f);
            CHECK(vec[2] == 3.0f);
        }
    }

    SECTION("unary negation")
    {
        SECTION("returns the RHS vector with each element negated")
        {
            Vector3 vecArg(1.0f, 2.0f, 3.0f);
            Vector3 vec = -vecArg;
            CHECK(vec[0] == -1.0f);
            CHECK(vec[1] == -2.0f);
            CHECK(vec[2] == -3.0f);
        }
    }

    SECTION("vector addition")
    {
        SECTION("returns the sum of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            Vector3 vecSum = vec1 + vec2;
            CHECK(vecSum[0] == 2.0f);
            CHECK(vecSum[1] == 2.0f);
            CHECK(vecSum[2] == 2.0f);
        }
    }

    SECTION("vector addition assignment")
    {
        SECTION("sets the LHS vector to the sum of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            vec1 += vec2;
            CHECK(vec1[0] == 2.0f);
            CHECK(vec1[1] == 2.0f);
            CHECK(vec1[2] == 2.0f);
        }
    }

    SECTION("vector subtraction")
    {
        SECTION("returns the difference of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            Vector3 vecDiff = vec1 - vec2;
            CHECK(vecDiff[0] == 0.0f);
            CHECK(vecDiff[1] == 0.0f);
            CHECK(vecDiff[2] == 0.0f);
        }
    }

    SECTION("vector subtraction assignment")
    {
        SECTION("sets the LHS vector to the difference of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            vec1 -= vec2;
            CHECK(vec1[0] == 0.0f);
            CHECK(vec1[1] == 0.0f);
            CHECK(vec1[2] == 0.0f);
        }
    }

    SECTION("vector multiplication")
    {
        SECTION("returns the Hadamard product of the LHS and RHS vectors")
        {
            Vector3 vec1(2.0f, 2.0f, 2.0f);
            Vector3 vec2(2.0f, 2.0f, 2.0f);
            Vector3 vecProduct = vec1 * vec2;
            CHECK(vecProduct[0] == 4.0f);
            CHECK(vecProduct[1] == 4.0f);
            CHECK(vecProduct[2] == 4.0f);
        }
    }

    SECTION("vector multiplication assignment")
    {
        SECTION("sets the LHS vector to the Hadamard product of the LHS and RHS vectors")
        {
            Vector3 vec1(2.0f, 2.0f, 2.0f);
            Vector3 vec2(2.0f, 2.0f, 2.0f);
            vec1 *= vec2;
            CHECK(vec1[0] == 4.0f);
            CHECK(vec1[1] == 4.0f);
            CHECK(vec1[2] == 4.0f);
        }
    }

    SECTION("vector division")
    {
        SECTION("returns the Hadamard quotient of the LHS and RHS vectors")
        {
            Vector3 vec1(2.0f, 2.0f, 2.0f);
            Vector3 vec2(2.0f, 2.0f, 2.0f);
            Vector3 vecQuotient = vec1 / vec2;
            CHECK(vecQuotient[0] == 1.0f);
            CHECK(vecQuotient[1] == 1.0f);
            CHECK(vecQuotient[2] == 1.0f);
        }
    }

    SECTION("vector division assignment")
    {
        SECTION("sets the LHS vector to the Hadamard quotient of the LHS and RHS vectors")
        {
            Vector3 vec1(2.0f, 2.0f, 2.0f);
            Vector3 vec2(2.0f, 2.0f, 2.0f);
            vec1 /= vec2;
            CHECK(vec1[0] == 1.0f);
            CHECK(vec1[1] == 1.0f);
            CHECK(vec1[2] == 1.0f);
        }
    }

    SECTION("scalar multiplication")
    {
        SECTION("returns the product of the LHS vector and the RHS scalar")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vecProduct = vec1 * 3.0f;
            CHECK(vecProduct[0] == 3.0f);
            CHECK(vecProduct[1] == 3.0f);
            CHECK(vecProduct[2] == 3.0f);
        }
    }

    SECTION("scalar multiplication assignment")
    {
        SECTION("sets the LHS vector to the product of the LHS vector and the RHS scalar")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            vec1 *= 3.0f;
            CHECK(vec1[0] == 3.0f);
            CHECK(vec1[1] == 3.0f);
            CHECK(vec1[2] == 3.0f);
        }
    }

    SECTION("scalar division")
    {
        SECTION("returns the quotient of the LHS vector and the RHS scalar")
        {
            Vector3 vec1(3.0f, 3.0f, 3.0f);
            Vector3 vecQuotient = vec1 / 3.0f;
            CHECK(vecQuotient[0] == 1.0f);
            CHECK(vecQuotient[1] == 1.0f);
            CHECK(vecQuotient[2] == 1.0f);
        }
    }

    SECTION("scalar division assignment")
    {
        SECTION("sets the LHS vector to the quotient of the LHS vector and the RHS scalar")
        {
            Vector3 vec1(3.0f, 3.0f, 3.0f);
            vec1 /= 3.0f;
            CHECK(vec1[0] == 1.0f);
            CHECK(vec1[1] == 1.0f);
            CHECK(vec1[2] == 1.0f);
        }
    }

    SECTION("equal comparison")
    {
        SECTION("returns true when the LHS and RHS vectors are equal")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            bool equal = vec1 == vec2;
            CHECK(equal);
        }

        SECTION("returns false when the LHS and RHS vectors are not equal")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 2.0f, 1.0f);
            bool equal = vec1 == vec2;
            REQUIRE_FALSE(equal);
        }
    }

    SECTION("not equal comparison")
    {
        SECTION("returns false when the LHS and RHS vectors are equal")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            bool equal = vec1 != vec2;
            REQUIRE_FALSE(equal);
        }

        SECTION("returns true when the LHS and RHS vectors are not equal")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 2.0f, 1.0f);
            bool equal = vec1 != vec2;
            CHECK(equal);
        }
    }

    SECTION("dot")
    {
        SECTION("returns the dot product of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 2.0f, 3.0f);
            Vector3 vec2(3.0f, 2.0f, 1.0f);
            float dot = vec1.dot(vec2);
            CHECK(dot == 10.0f);
        }
    }

    SECTION("squaredLength")
    {
        SECTION("returns the square of the length of the vector")
        {
            Vector3 vec(2.0f, 2.0f, 2.0f);
            float squaredLength = vec.squaredLength();
            CHECK(squaredLength == 12.0f);
        }
    }


    SECTION("length")
    {
        SECTION("returns length of the vector")
        {
            Vector3 vec(2.0f, 2.0f, 2.0f);
            float length = vec.length();
            CHECK(length == std::sqrt(12.0f));
        }
    }

    SECTION("reciprocal")
    {
        SECTION("returns the vector with the numerator and denominator of each element flipped")
        {
            Vector3 vec(2.0f, 2.0f, 2.0f);
            Vector3 reciprocal = vec.reciprocal();
            CHECK(reciprocal.x == 0.5f);
            CHECK(reciprocal.y == 0.5f);
            CHECK(reciprocal.z == 0.5f);
        }
    }

    SECTION("normalize")
    {
        SECTION("normalizes the vector")
        {
            Vector3 vec(1.0f, 0.0f, 1.0f);
            vec.normalize();
            CHECK(vec.x == std::sqrt(2.0f) / 2.0f);
            CHECK(vec.y == 0.0f);
            CHECK(vec.z == std::sqrt(2.0f) / 2.0f);
        }
    }

    SECTION("normalizedCopy")
    {
        SECTION("returns a normalized copy of the vector")
        {
            Vector3 vec(1.0f, 0.0f, 1.0f);
            Vector3 vec2 = vec.normalizedCopy();
            CHECK(vec2.x == std::sqrt(2.0f) / 2.0f);
            CHECK(vec2.y == 0.0f);
            CHECK(vec2.z == std::sqrt(2.0f) / 2.0f);
        }
    }
}

TEST_CASE("Vector SIMD 128F", "[Vector]")
{
    using Vector3 = tov::math::Vector<3, tov::math::SIMD::_128F>;

    SECTION("element constructor")
    {
        SECTION("accepts arguments for each element")
        {
            Vector3 vec(1.0f, 2.0f, 3.0f);
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 2.0f);
            CHECK(vec[2] == 3.0f);
        }
    }

    SECTION("copy constructor")
    {	
        SECTION("accepts a Vector argument")
        {
            Vector3 vecArg(1.0f, 1.0f, 1.0f);
            Vector3 vec(vecArg);
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 1.0f);
            CHECK(vec[2] == 1.0f);
        }
    }

    SECTION("assignment")
    {
        SECTION("sets the LHS vector to the RHS vector")
        {
            Vector3 vecArg(1.0f, 1.0f, 1.0f);
            Vector3 vec = vecArg;
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 1.0f);
            CHECK(vec[2] == 1.0f);
        }
    }

    SECTION("subscript")
    {
        SECTION("returns the vector element at the given index")
        {
            Vector3 vec(1.0f, 2.0f, 3.0f);
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 2.0f);
            CHECK(vec[2] == 3.0f);
        }
    }

    SECTION("unary plus")
    {
        SECTION("returns the RHS vector")
        {
            Vector3 vecArg(1.0f, 2.0f, 3.0f);
            Vector3 vec = +vecArg;
            CHECK(vec[0] == 1.0f);
            CHECK(vec[1] == 2.0f);
            CHECK(vec[2] == 3.0f);
        }
    }

    SECTION("unary negation")
    {
        SECTION("returns the RHS vector with each element negated")
        {
            Vector3 vecArg(1.0f, 2.0f, 3.0f);
            Vector3 vec = -vecArg;
            CHECK(vec[0] == -1.0f);
            CHECK(vec[1] == -2.0f);
            CHECK(vec[2] == -3.0f);
        }
    }

    SECTION("vector addition")
    {
        SECTION("returns the sum of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            Vector3 vecSum = vec1 + vec2;
            CHECK(vecSum[0] == 2.0f);
            CHECK(vecSum[1] == 2.0f);
            CHECK(vecSum[2] == 2.0f);
        }
    }

    SECTION("vector addition assignment")
    {
        SECTION("sets the LHS vector to the sum of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            vec1 += vec2;
            CHECK(vec1[0] == 2.0f);
            CHECK(vec1[1] == 2.0f);
            CHECK(vec1[2] == 2.0f);
        }
    }

    SECTION("vector subtraction")
    {
        SECTION("returns the difference of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            Vector3 vecDiff = vec1 - vec2;
            CHECK(vecDiff[0] == 0.0f);
            CHECK(vecDiff[1] == 0.0f);
            CHECK(vecDiff[2] == 0.0f);
        }
    }

    SECTION("vector subtraction assignment")
    {
        SECTION("sets the LHS vector to the difference of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            vec1 -= vec2;
            CHECK(vec1[0] == 0.0f);
            CHECK(vec1[1] == 0.0f);
            CHECK(vec1[2] == 0.0f);
        }
    }

    SECTION("vector multiplication")
    {
        SECTION("returns the Hadamard product of the LHS and RHS vectors")
        {
            Vector3 vec1(2.0f, 2.0f, 2.0f);
            Vector3 vec2(2.0f, 2.0f, 2.0f);
            Vector3 vecProduct = vec1 * vec2;
            CHECK(vecProduct[0] == 4.0f);
            CHECK(vecProduct[1] == 4.0f);
            CHECK(vecProduct[2] == 4.0f);
        }
    }

    SECTION("vector multiplication assignment")
    {
        SECTION("sets the LHS vector to the Hadamard product of the LHS and RHS vectors")
        {
            Vector3 vec1(2.0f, 2.0f, 2.0f);
            Vector3 vec2(2.0f, 2.0f, 2.0f);
            vec1 *= vec2;
            CHECK(vec1[0] == 4.0f);
            CHECK(vec1[1] == 4.0f);
            CHECK(vec1[2] == 4.0f);
        }
    }

    SECTION("vector division")
    {
        SECTION("returns the Hadamard quotient of the LHS and RHS vectors")
        {
            Vector3 vec1(2.0f, 2.0f, 2.0f);
            Vector3 vec2(2.0f, 2.0f, 2.0f);
            Vector3 vecQuotient = vec1 / vec2;
            CHECK(vecQuotient[0] == 1.0f);
            CHECK(vecQuotient[1] == 1.0f);
            CHECK(vecQuotient[2] == 1.0f);
        }
    }

    SECTION("vector division assignment")
    {
        SECTION("sets the LHS vector to the Hadamard quotient of the LHS and RHS vectors")
        {
            Vector3 vec1(2.0f, 2.0f, 2.0f);
            Vector3 vec2(2.0f, 2.0f, 2.0f);
            vec1 /= vec2;
            CHECK(vec1[0] == 1.0f);
            CHECK(vec1[1] == 1.0f);
            CHECK(vec1[2] == 1.0f);
        }
    }

    SECTION("scalar multiplication")
    {
        SECTION("returns the product of the LHS vector and the RHS scalar")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vecProduct = vec1 * 3.0f;
            CHECK(vecProduct[0] == 3.0f);
            CHECK(vecProduct[1] == 3.0f);
            CHECK(vecProduct[2] == 3.0f);
        }
    }

    SECTION("scalar multiplication assignment")
    {
        SECTION("sets the LHS vector to the product of the LHS vector and the RHS scalar")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            vec1 *= 3.0f;
            CHECK(vec1[0] == 3.0f);
            CHECK(vec1[1] == 3.0f);
            CHECK(vec1[2] == 3.0f);
        }
    }

    SECTION("scalar division")
    {
        SECTION("returns the quotient of the LHS vector and the RHS scalar")
        {
            Vector3 vec1(3.0f, 3.0f, 3.0f);
            Vector3 vecQuotient = vec1 / 3.0f;
            CHECK(vecQuotient[0] == 1.0f);
            CHECK(vecQuotient[1] == 1.0f);
            CHECK(vecQuotient[2] == 1.0f);
        }
    }

    SECTION("scalar division assignment")
    {
        SECTION("sets the LHS vector to the quotient of the LHS vector and the RHS scalar")
        {
            Vector3 vec1(3.0f, 3.0f, 3.0f);
            vec1 /= 3.0f;
            CHECK(vec1[0] == 1.0f);
            CHECK(vec1[1] == 1.0f);
            CHECK(vec1[2] == 1.0f);
        }
    }

    SECTION("equality operator")
    {
        SECTION("returns true when the LHS and RHS vectors are equal")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            bool equal = vec1 == vec2;
            CHECK(equal);
        }

        SECTION("returns false when the LHS and RHS vectors are not equal")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 2.0f, 1.0f);
            bool equal = vec1 == vec2;
            REQUIRE_FALSE(equal);
        }
    }

    SECTION("inequality operator")
    {
        SECTION("returns false when the LHS and RHS vectors are equal")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 1.0f, 1.0f);
            bool equal = vec1 != vec2;
            REQUIRE_FALSE(equal);
        }

        SECTION("returns true when the LHS and RHS vectors are not equal")
        {
            Vector3 vec1(1.0f, 1.0f, 1.0f);
            Vector3 vec2(1.0f, 2.0f, 1.0f);
            bool equal = vec1 != vec2;
            CHECK(equal);
        }
    }

    SECTION("dot")
    {
        SECTION("returns the dot product of the LHS and RHS vectors")
        {
            Vector3 vec1(1.0f, 2.0f, 3.0f);
            Vector3 vec2(3.0f, 2.0f, 1.0f);
            float dot = vec1.dot(vec2);
            CHECK(dot == 10.0f);
        }
    }

    SECTION("squaredLength")
    {
        SECTION("returns the square of the length of the vector")
        {
            Vector3 vec(2.0f, 2.0f, 2.0f);
            float squaredLength = vec.squaredLength();
            CHECK(squaredLength == 12.0f);
        }
    }


    SECTION("length")
    {
        SECTION("returns length of the vector")
        {
            Vector3 vec(2.0f, 2.0f, 2.0f);
            float length = vec.length();
            CHECK(length == std::sqrt(12.0f));
        }
    }

    SECTION("reciprocal")
    {
        SECTION("returns the vector with the numerator and denominator of each element flipped")
        {
            Vector3 vec(2.0f, 2.0f, 2.0f);
            Vector3 reciprocal = vec.reciprocal();
            CHECK(reciprocal.x == 0.5f);
            CHECK(reciprocal.y == 0.5f);
            CHECK(reciprocal.z == 0.5f);
        }
    }

    SECTION("normalize")
    {
        SECTION("normalizes the vector")
        {
            Vector3 vec(1.0f, 0.0f, 1.0f);
            vec.normalize();
            CHECK(vec.x == std::sqrt(2.0f) / 2.0f);
            CHECK(vec.y == 0.0f);
            CHECK(vec.z == std::sqrt(2.0f) / 2.0f);
        }
    }

    SECTION("normalizedCopy")
    {
        SECTION("returns a normalized copy of the vector")
        {
            Vector3 vec(1.0f, 0.0f, 1.0f);
            Vector3 vec2 = vec.normalizedCopy();
            CHECK(vec2.x == std::sqrt(2.0f) / 2.0f);
            CHECK(vec2.y == 0.0f);
            CHECK(vec2.z == std::sqrt(2.0f) / 2.0f);
        }
    }
}

TEST_CASE("Vector2", "[Vector2]")
{
    SECTION("element constructor")
    {
        SECTION("accepts arguments for x and y")
        {
            tov::math::Vector2 vec(1.0f, 1.0f);
            CHECK(vec.x == 1.0f);
            CHECK(vec.y == 1.0f);
        }
    }
}

TEST_CASE("Vector3", "[Vector3]")
{
    SECTION("element constructor")
    {
        SECTION("accepts arguments for x, y, and z")
        {
            tov::math::Vector3 vec(1.0f, 1.0f, 1.0f);
            CHECK(vec.x == 1.0f);
            CHECK(vec.y == 1.0f);
            CHECK(vec.z == 1.0f);
        }
    }

    SECTION("cross")
    {
        SECTION("returns the cross product of the LHS and RHS vectors")
        {
            tov::math::Vector3 vec1(1.0f, 2.0f, 3.0f);
            tov::math::Vector3 vec2(2.0f, 3.0f, 4.0f);
            tov::math::Vector3 vecCrossProduct = vec1.cross(vec2);
            CHECK(vecCrossProduct.x == -1.0f);
            CHECK(vecCrossProduct.y == 2.0f);
            CHECK(vecCrossProduct.z == -1.0f);
        }
    }

    SECTION("crossAssign")
    {
        SECTION("sets the LHS to the cross product of the LHS and RHS vectors")
        {
            tov::math::Vector3 vec1(1.0f, 2.0f, 3.0f);
            tov::math::Vector3 vec2(2.0f, 3.0f, 4.0f);
            vec1.crossAssign(vec2);
            CHECK(vec1.x == -1.0f);
            CHECK(vec1.y == 2.0f);
            CHECK(vec1.z == -1.0f);
        }
    }
}

TEST_CASE("Vector4", "[Vector4]")
{
    SECTION("element constructor")
    {
        SECTION("accepts arguments for x, y, z,and w")
        {
            tov::math::Vector4 vec(1.0f, 1.0f, 1.0f, 1.0f);
            CHECK(vec.x == 1.0f);
            CHECK(vec.y == 1.0f);
            CHECK(vec.z == 1.0f);
            CHECK(vec.w == 1.0f);
        }
    }
}
