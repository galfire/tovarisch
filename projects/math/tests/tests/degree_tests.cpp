#include "test_helper.h"

#include <tov/math/degree.h>
#include <tov/math/radian.h>

TEST_CASE("Degree", "[Degree]")
{
    SECTION("valueDegrees")
    {
        SECTION("returns the value in degrees")
        {
            tov::math::Degree d(90.0f);
            CHECK(d.valueDegrees() == 90.0f);
        }
    }

    SECTION("Degree assignment")
    {
        SECTION("sets the LHS degree to the RHS degree")
        {
            tov::math::Degree degArg(90.0f);
            tov::math::Degree d(0.0f);
            d = degArg;
            CHECK(d.valueDegrees() == 90.0f);
        }
    }

    SECTION("unary plus operator")
    {
        SECTION("returns the degree")
        {
            tov::math::Degree degArg(90.0f);
            tov::math::Degree d = +degArg;
            CHECK(d.valueDegrees() == 90.0f);
        }
    }

    SECTION("unary negation operator")
    {
        SECTION("returns the degree with a negated value")
        {
            tov::math::Degree degArg(90.0f);
            tov::math::Degree d = -degArg;
            CHECK(d.valueDegrees() == -90.0f);
        }
    }

    SECTION("addition")
    {
        SECTION("returns the degree sum of the LHS and RHS degrees")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            tov::math::Degree dSum = d1 + d2;
            CHECK(dSum.valueDegrees() == 180.0f);
        }
    }

    SECTION("addition assignment")
    {
        SECTION("sets the LHS degree to the degree sum of the LHS and RHS degrees")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            d1 += d2;
            CHECK(d1.valueDegrees() == 180.0f);
        }
    }

    SECTION("subtraction")
    {
        SECTION("returns the degree difference of the LHS and RHS degrees")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            tov::math::Degree dDiff = d1 - d2;
            CHECK(dDiff.valueDegrees() == 0.0f);
        }
    }

    SECTION("subtraction assignment")
    {
        SECTION("sets the LHS degree to the degree difference of the LHS and RHS degrees")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            d1 -= d2;
            CHECK(d1.valueDegrees() == 0.0f);
        }
    }

    SECTION("multiplication")
    {
        SECTION("returns the degree product of the LHS degree and RHS scalar")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree dProduct = d1 * 4;
            CHECK(dProduct.valueDegrees() == 360.0f);
        }
    }

    SECTION("multiplication assignment")
    {
        SECTION("sets the LHS degree to the degree product of the LHS degree and RHS scalar")
        {
            tov::math::Degree d1(90.0f);
            d1 *= 4;
            CHECK(d1.valueDegrees() == 360.0f);
        }
    }

    SECTION("division")
    {
        SECTION("returns the degree quotient of the LHS degree and RHS scalar")
        {
            tov::math::Degree d1(360.0f);
            tov::math::Degree dQuotient = d1 / 4;
            CHECK(dQuotient.valueDegrees() == 90.0f);
        }
    }

    SECTION("division assignment")
    {
        SECTION("sets the LHS degree to the degree quotient of the LHS degree and RHS scalar")
        {
            tov::math::Degree d1(360.0f);
            d1 /= 4;
            CHECK(d1.valueDegrees() == 90.0f);
        }
    }

    SECTION("equality operator")
    {
        SECTION("returns true when the LHS and RHS degrees are equal")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            CHECK(d1 == d2);
        }

        SECTION("returns false when the LHS and RHS degrees are not equal")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(270.0f);
            CHECK_FALSE(d1 == d2);
        }
    }

    SECTION("inequality operator")
    {
        SECTION("returns false when the LHS and RHS degrees are equal")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            CHECK_FALSE(d1 != d2);
        }

        SECTION("returns true when the LHS and RHS degrees are not equal")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(270.0f);
            CHECK(d1 != d2);
        }
    }

    SECTION("less than operator")
    {
        SECTION("returns true when the LHS degree is less than the RHS degree")
        {
            tov::math::Degree d1(45.0f);
            tov::math::Degree d2(90.0f);
            CHECK(d1 < d2);
        }

        SECTION("returns false when the LHS degree is greater than the RHS degree")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(45.0f);
            CHECK_FALSE(d1 < d2);
        }

        SECTION("returns false when the LHS degree is equal to the RHS degree")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            CHECK_FALSE(d1 < d2);
        }
    }

    SECTION("less than or equal operator")
    {
        SECTION("returns true when the LHS degree is less than the RHS degree")
        {
            tov::math::Degree d1(45.0f);
            tov::math::Degree d2(90.0f);
            CHECK(d1 <= d2);
        }

        SECTION("returns false when the LHS degree is greater than the RHS degree")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(45.0f);
            CHECK_FALSE(d1 <= d2);
        }

        SECTION("returns true when the LHS degree is equal to the RHS degree")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            CHECK(d1 <= d2);
        }
    }

    SECTION("greather than operator")
    {
        SECTION("returns false when the LHS degree is less than the RHS degree")
        {
            tov::math::Degree d1(45.0f);
            tov::math::Degree d2(90.0f);
            CHECK_FALSE(d1 > d2);
        }

        SECTION("returns true when the LHS degree is greater than the RHS degree")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(45.0f);
            CHECK(d1 > d2);
        }

        SECTION("returns false when the LHS degree is equal to the RHS degree")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            CHECK_FALSE(d1 > d2);
        }
    }

    SECTION("greather than or equal operator")
    {
        SECTION("returns false when the LHS degree is less than the RHS degree")
        {
            tov::math::Degree d1(45.0f);
            tov::math::Degree d2(90.0f);
            CHECK_FALSE(d1 >= d2);
        }

        SECTION("returns true when the LHS degree is greater than the RHS degree")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(45.0f);
            CHECK(d1 >= d2);
        }

        SECTION("returns true when the LHS degree is equal to the RHS degree")
        {
            tov::math::Degree d1(90.0f);
            tov::math::Degree d2(90.0f);
            CHECK(d1 >= d2);
        }
    }

    SECTION("radian constructor")
    {
        SECTION("accepts a radian")
        {
            tov::math::Radian r(2.0f * tov::math::PI);
            tov::math::Degree d(r);
            CHECK(d.valueDegrees() == 360.0f);
        }
    }

    SECTION("toRadian")
    {
        SECTION("returns an equivalent radian")
        {
            tov::math::Degree d(360.0f);
            tov::math::Radian r = d.toRadian();
            CHECK(r.valueRadians() == 2.0f * tov::math::PI);
        }
    }

    SECTION("valueRadians")
    {
        SECTION("returns the value in radians")
        {
            tov::math::Degree d(180.0f);
            float vr = d.valueRadians();
            CHECK(vr == tov::math::PI);
        }
    }

    SECTION("_deg literal")
    {
        SECTION("returns a degree of the given value")
        {
            using namespace tov::math;
            tov::math::Degree d = 180.0_deg;
            CHECK(d.valueDegrees() == 180.0f);
        }
    }
}
