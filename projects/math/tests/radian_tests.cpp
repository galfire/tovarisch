#include "test_helper.h"

#include <tov/math/radian.h>
#include <tov/math/degree.h>

TEST_CASE("Radian", "[Radian]")
{
	const float PI = tov::math::PI;

	SECTION("assignment constructor")
	{
		tov::math::Radian r = PI;
		REQUIRE(r.valueRadians() == PI);
	}

	SECTION("valueRadian")
	{
		SECTION("returns the value in radians")
		{
			tov::math::Radian r(PI);
			REQUIRE(r.valueRadians() == PI);
		}
	}

	SECTION("radian assignment")
	{
		SECTION("sets the LHS radian to the RHS radian")
		{
			tov::math::Radian rArg(PI);
			tov::math::Radian r(0.0f);
			r = rArg;;
			REQUIRE(r.valueRadians() == PI);
		}
	}

	SECTION("unary plus operator")
	{
		SECTION("returns the radian")
		{
			tov::math::Radian rArg(PI);
			tov::math::Radian r = +rArg;
			REQUIRE(r.valueRadians() == PI);
		}
	}

	SECTION("unary negation operator")
	{
		SECTION("returns the valueRadians with a negated value")
		{
			tov::math::Radian rArg(PI);
			tov::math::Radian r = -rArg;
			REQUIRE(r.valueRadians() == -PI);
		}
	}

	SECTION("addition")
	{
		SECTION("returns the radian sum of the LHS and RHS radians")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			tov::math::Radian rSum = r1 + r2;
			REQUIRE(rSum.valueRadians() == 2 * PI);
		}
	}

	SECTION("addition assignment")
	{
		SECTION("sets the LHS radian to the radian sum of the LHS and RHS radians")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			r1 += r2;
			REQUIRE(r1.valueRadians() == 2 * PI);
		}
	}

	SECTION("subtraction")
	{
		SECTION("returns the radian difference of the LHS and RHS radians")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			tov::math::Radian rDiff = r1 - r2;
			REQUIRE(rDiff.valueRadians() == 0.0f);
		}
	}

	SECTION("subtraction assignment")
	{
		SECTION("sets the LHS radian to the radian difference of the LHS and RHS radians")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			r1 -= r2;
			REQUIRE(r1.valueRadians() == 0.0f);
		}
	}

	SECTION("multiplication")
	{
		SECTION("returns the radian product of the LHS radian and RHS scalar")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian rProduct = r1 * 2;
			REQUIRE(rProduct.valueRadians() == 2 * PI);
		}
	}

	SECTION("multiplication assignment")
	{
		SECTION("sets the LHS radian to the radian product of the LHS radian and RHS scalar")
		{
			tov::math::Radian r1(PI);
			r1 *= 2;
			REQUIRE(r1.valueRadians() == 2 * PI);
		}
	}

	SECTION("division")
	{
		SECTION("returns the radian quotient of the LHS radian and RHS scalar")
		{
			tov::math::Radian r1(2 * PI);
			tov::math::Radian rQuotient = r1 / 2;
			REQUIRE(rQuotient.valueRadians() == PI);
		}
	}

	SECTION("division assignment")
	{
		SECTION("sets the LHS radian to the radian quotient of the LHS radian and RHS scalar")
		{
			tov::math::Radian r1(2 * PI);
			r1 /= 2;
			REQUIRE(r1.valueRadians() == PI);
		}
	}

	SECTION("equality operator")
	{
		SECTION("returns true when the LHS and RHS radians are equal")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			REQUIRE(r1 == r2);
		}

		SECTION("returns false when the LHS and RHS radians are not equal")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(2 * PI);
			REQUIRE_FALSE(r1 == r2);
		}
	}

	SECTION("inequality operator")
	{
		SECTION("returns false when the LHS and RHS radians are equal")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			REQUIRE_FALSE(r1 != r2);
		}

		SECTION("returns true when the LHS and RHS radians are not equal")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(2 * PI);
			REQUIRE(r1 != r2);
		}
	}

	SECTION("less than operator")
	{
		SECTION("returns true when the LHS radian is less than the RHS radian")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(2 * PI);
			REQUIRE(r1 < r2);
		}

		SECTION("returns false when the LHS radian is greater than the RHS radian")
		{
			tov::math::Radian r1(2 * PI);
			tov::math::Radian r2(PI);
			REQUIRE_FALSE(r1 < r2);
		}

		SECTION("returns false when the LHS radian is equal to the RHS radian")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			REQUIRE_FALSE(r1 < r2);
		}
	}

	SECTION("less than or equal operator")
	{
		SECTION("returns true when the LHS radian is less than the RHS radian")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(2 * PI);
			REQUIRE(r1 <= r2);
		}

		SECTION("returns false when the LHS radian is greater than the RHS radian")
		{
			tov::math::Radian r1(2 * PI);
			tov::math::Radian r2(PI);
			REQUIRE_FALSE(r1 <= r2);
		}

		SECTION("returns true when the LHS radian is equal to the RHS radian")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			REQUIRE(r1 <= r2);
		}
	}

	SECTION("greather than operator")
	{
		SECTION("returns false when the LHS radian is less than the RHS radian")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(2 * PI);
			REQUIRE_FALSE(r1 > r2);
		}

		SECTION("returns true when the LHS radian is greater than the RHS radian")
		{
			tov::math::Radian r1(2 * PI);
			tov::math::Radian r2(PI);
			REQUIRE(r1 > r2);
		}

		SECTION("returns false when the LHS radian is equal to the RHS radian")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(2 * PI);
			REQUIRE_FALSE(r1 > r2);
		}
	}

	SECTION("greather than or equal operator")
	{
		SECTION("returns false when the LHS radian is less than the RHS radian")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(2 * PI);
			REQUIRE_FALSE(r1 >= r2);
		}

		SECTION("returns true when the LHS radian is greater than the RHS radian")
		{
			tov::math::Radian r1(2 * PI);
			tov::math::Radian r2(PI);
			REQUIRE(r1 >= r2);
		}

		SECTION("returns true when the LHS radian is equal to the RHS radian")
		{
			tov::math::Radian r1(PI);
			tov::math::Radian r2(PI);
			REQUIRE(r1 >= r2);
		}
	}

	SECTION("degree constructor")
	{
		SECTION("accepts a degree")
		{
			tov::math::Degree d(180.0f);
			tov::math::Radian r(d);
			REQUIRE(r.valueRadians() == PI);
		}
	}

	SECTION("toDegree")
	{
		SECTION("returns an equivalent degree")
		{
			tov::math::Radian r(2.0f * tov::math::PI);
			tov::math::Degree d = r.toDegree();
			REQUIRE(d.valueDegrees() == 360.0f);
		}
	}

	SECTION("valueDegrees")
	{
		SECTION("returns the value in degrees")
		{
			tov::math::Radian r(PI);
			float dr = r.valueDegrees();
			REQUIRE(dr == 180.0f);
		}
	}

	SECTION("_reg literal")
	{
		SECTION("returns a radian of the given value")
		{
			using namespace tov::math;
			tov::math::Radian r = 3.1415926535_rad;
			REQUIRE(r.valueRadians() == PI);
		}
	}
}
