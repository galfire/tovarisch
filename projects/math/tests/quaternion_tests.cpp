#include "test_helper.h"

#include <tov/math/quaternion.h>

#include <iostream>

TEST_CASE("Quaternion", "[Quaternion]")
{
    float PI = tov::math::PI;

    SECTION("element constructor")
    {
        SECTION("accepts arguments for w, x, y, and z")
        {
            tov::math::Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
            REQUIRE(q.w == 1.0f);
            REQUIRE(q.x == 2.0f);
            REQUIRE(q.y == 3.0f);
            REQUIRE(q.z == 4.0f);
        }
    }

    SECTION("angle-axis constructor")
    {
        SECTION("accepts an angle in radians and vector axis")
        {
            tov::math::Radian r(PI);
            tov::math::Vector3 axis(1.0f, 1.0f, 1.0f);
            tov::math::Quaternion q(r, axis);
            REQUIRE(q.getAngle() == tov::math::Radian(PI));
            auto axis_expected = tov::math::Vector3(1.0f, 1.0f, 1.0f).normalize();
            auto axis_actual = q.getAxis();
            REQUIRE(axis_actual == axis_expected);
        }
    }

    SECTION("rotate")
    {
        SECTION("rotates the given vector")
        {
            tov::math::Radian r(PI);
            tov::math::Vector3 axis = tov::math::Vector3::UNIT_Z;
            tov::math::Quaternion q(r, axis);

            tov::math::Vector3 v(0.0f, 1.0f, 0.0f);
            tov::math::Vector3 v2 = q.rotate(v);
            REQUIRE(v2.x == 0.0f);
            REQUIRE(v2.y == -1.0f);
            REQUIRE(v2.z == 0.0f);
        }

        SECTION("can be invoked with the operator *")
        {
            tov::math::Radian r(PI);
            tov::math::Vector3 axis = tov::math::Vector3::UNIT_Z;
            tov::math::Quaternion q(r, axis);

            tov::math::Vector3 v(0.0f, 1.0f, 0.0f);
            tov::math::Vector3 v2 = q * v;
            REQUIRE(v2.x == 0.0f);
            REQUIRE(v2.y == -1.0f);
            REQUIRE(v2.z == 0.0f);
        }
    }

    SECTION("accumulate")
    {
        tov::math::Radian r1(PI * 0.5f);
        tov::math::Vector3 axis1 = tov::math::Vector3::UNIT_Z;
        tov::math::Quaternion q1(r1, axis1);

        tov::math::Radian r2(PI * 0.5f);
        tov::math::Vector3 axis2 = tov::math::Vector3::UNIT_Z;
        tov::math::Quaternion q2(r2, axis2);

        SECTION("returns a quaternion that is the composition of this quaternion and the given quatenrion")
        {
            tov::math::Quaternion q3 = q1.accumulate(q2);
            REQUIRE(q3.getAngle() == tov::math::Radian(PI));
            auto axis_expected = tov::math::Vector3::UNIT_Z;
            auto axis_actual = q3.getAxis();
            REQUIRE(axis_actual == axis_expected);
        }

        SECTION("can be invoked with the operator *")
        {
            tov::math::Quaternion q3 = q1 * q2;
            REQUIRE(q3.getAngle() == tov::math::Radian(PI));
            auto axis_expected = tov::math::Vector3::UNIT_Z;
            auto axis_actual = q3.getAxis();
            REQUIRE(axis_actual == axis_expected);
        }
    }

    SECTION("accumulateAssign")
    {
        tov::math::Radian r1(PI * 0.5f);
        tov::math::Vector3 axis1 = tov::math::Vector3::UNIT_Z;
        tov::math::Quaternion q1(r1, axis1);

        tov::math::Radian r2(PI * 0.5f);
        tov::math::Vector3 axis2 = tov::math::Vector3::UNIT_Z;
        tov::math::Quaternion q2(r2, axis2);

        SECTION("sets this quaternion to the composition of this quaternion and the given quatenrion")
        {
            q1.accumulateAssign(q2);
            REQUIRE(q1.getAngle() == tov::math::Radian(PI));
            auto axis_expected = tov::math::Vector3::UNIT_Z;
            auto axis_actual = q1.getAxis();
            REQUIRE(axis_actual == axis_expected);
        }

        SECTION("can be invoked with the operator *=")
        {
            q1 *= q2;
            REQUIRE(q1.getAngle() == tov::math::Radian(PI));
            auto axis_expected = tov::math::Vector3::UNIT_Z;
            auto axis_actual = q1.getAxis();
            REQUIRE(axis_actual == axis_expected);
        }
    }

    SECTION("getAngle")
    {
        SECTION("returns the angle in radians")
        {
            tov::math::Radian r(PI);
            tov::math::Vector3 axis = tov::math::Vector3::UNIT_Z;
            tov::math::Quaternion q(r, axis);
            REQUIRE(q.getAngle() == tov::math::Radian(PI));
        }
    }

    SECTION("getAxis")
    {
        SECTION("returns the axis")
        {
            tov::math::Radian r(PI);
            tov::math::Vector3 axis = tov::math::Vector3::UNIT_Z;
            tov::math::Quaternion q(r, axis);
            REQUIRE(q.getAxis() == tov::math::Vector3::UNIT_Z);
        }
    }

    SECTION("toRotationMatrix")
    {
        SECTION("returns the equivalent rotation matrix")
        {
            tov::math::Radian r(PI);
            tov::math::Vector3 axis = tov::math::Vector3::UNIT_Z;
            tov::math::Quaternion q(r, axis);
            tov::math::Matrix3 m = q.toRotationMatrix();

            REQUIRE(cmpf(m[0][0], tov::math::cos(r)));
            REQUIRE(cmpf(m[0][1], -tov::math::sin(r)));
            REQUIRE(cmpf(m[0][2], 0.0f));
            REQUIRE(cmpf(m[1][0], tov::math::sin(r)));
            REQUIRE(cmpf(m[1][1], tov::math::cos(r)));
            REQUIRE(cmpf(m[1][2], 0.0f));
            REQUIRE(cmpf(m[2][0], 0.0f));
            REQUIRE(cmpf(m[2][1], 0.0f));
            REQUIRE(cmpf(m[2][2], 1.0f));
        }
    }
}

