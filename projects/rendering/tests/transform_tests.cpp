#include "test_helper.h"

#include <tov/rendering/transform.h>

#include <tov/math/quaternion.h>
#include <tov/math/radian.h>
#include <tov/math/vector.h>

TEST_CASE("Transform", "[Transform]")
{
    SECTION("default constructor")
    {
        tov::rendering::Transform transform;

        SECTION("sets the translation vector to the zero vector")
        {
            auto translation = transform.getTranslation();
            REQUIRE(translation == tov::math::Vector3::ZERO);
        }

        SECTION("sets the rotation quaternion to the identity quaternion")
        {
            auto rotation = transform.getRotationQuaternion();
            REQUIRE(rotation == tov::math::Quaternion::IDENTITY);
        }

        SECTION("sets the scale vector to the unit scale vector")
        {
            auto scale = transform.getScale();
            REQUIRE(scale == tov::math::Vector3::UNIT_SCALE);
        }
    }

    SECTION("constructor")
    {
        tov::math::Vector3 expectedTranslation(1.0f, 1.0f, 1.0f);
        tov::math::Quaternion expectedRotation(tov::math::Radian(tov::math::PI), tov::math::Vector3::UNIT_X);
        tov::math::Vector3 expectedScale(2.0f, 2.0f, 2.0f);
        tov::rendering::Transform transform(expectedTranslation, expectedRotation, expectedScale);

        SECTION("sets the translation vector to the given vector")
        {
            auto translation = transform.getTranslation();
            REQUIRE(translation == expectedTranslation);
        }

        SECTION("sets the rotation quaternion to the given quaternion")
        {
            auto rotation = transform.getRotationQuaternion();
            REQUIRE(rotation == expectedRotation);
        }

        SECTION("sets the scale vector to the given vector")
        {
            auto scale = transform.getScale();
            REQUIRE(scale == expectedScale);
        }
    }

    SECTION("assignment operator")
    {
        SECTION("sets the LHS transform to the RHS vector")
        {
            tov::rendering::Transform transform;

            tov::math::Vector3 expectedTranslation(1.0f, 1.0f, 1.0f);
            tov::math::Quaternion expectedRotation(tov::math::Radian(tov::math::PI), tov::math::Vector3::UNIT_X);
            tov::math::Vector3 expectedScale(2.0f, 2.0f, 2.0f);
            tov::rendering::Transform transform2(expectedTranslation, expectedRotation, expectedScale);
            transform = transform2;

            auto translation = transform.getTranslation();
            auto rotation = transform.getRotationQuaternion();
            auto scale = transform.getScale();

            REQUIRE(translation == expectedTranslation);
            REQUIRE(rotation == expectedRotation);
            REQUIRE(scale == expectedScale);
        }
    }

    SECTION("equality operator")
    {
        tov::rendering::Transform transform1;
        tov::rendering::Transform transform2;

        SECTION("returns true when the LHS and RHS transforms are equal")
        {
            REQUIRE(transform1 == transform2);
        }

        SECTION("returns false when the LHS and RHS transforms are not equal")
        {
            transform2.translate(tov::math::Vector3(1.0f, 1.0f, 1.0f));

            REQUIRE_FALSE(transform1 == transform2);
        }
    }

    SECTION("inequality operator")
    {
        tov::rendering::Transform transform1;
        tov::rendering::Transform transform2;

        SECTION("returns false when the LHS and RHS transforms are equal")
        {
            REQUIRE_FALSE(transform1 != transform2);
        }

        SECTION("returns true when the LHS and RHS transforms are not equal")
        {
            transform2.translate(tov::math::Vector3(1.0f, 1.0f, 1.0f));

            REQUIRE(transform1 != transform2);
        }
    }

    SECTION("translate")
    {
        tov::rendering::Transform transform;

        SECTION("translates the transform by the given vector")
        {
            auto initialTranslation = transform.getTranslation();
            auto newTranslation = tov::math::Vector3(1.0f, 1.0f, 1.0f);
            transform.translate(newTranslation);

            auto translation = transform.getTranslation();
            REQUIRE(translation == initialTranslation + newTranslation);
        }
    }

    SECTION("setTranslation")
    {
        tov::rendering::Transform transform;

        SECTION("sets the transform's translation to the given vector")
        {
            auto newTranslation = tov::math::Vector3(1.0f, 1.0f, 1.0f);
            transform.setTranslation(newTranslation);

            auto translation = transform.getTranslation();
            REQUIRE(translation == newTranslation);
        }
    }

    SECTION("getTranslation")
    {
        tov::rendering::Transform transform;
        tov::math::Vector3 newTranslation(1.0f, 1.0f, 1.0f);
        transform.setTranslation(newTranslation);

        SECTION("returns the transform's translation")
        {
            auto translation = transform.getTranslation();
            REQUIRE(translation == newTranslation);
        }
    }

    SECTION("rotate")
    {
        tov::rendering::Transform transform;

        SECTION("rotates the transform by the given quaternion")
        {
            auto initialRotation = transform.getRotationQuaternion();
            auto newRotation = tov::math::Quaternion(tov::math::Radian(tov::math::PI), tov::math::Vector3::UNIT_Z);
            transform.rotate(newRotation);

            auto rotation = transform.getRotationQuaternion();
            REQUIRE(rotation == initialRotation * newRotation);
        }
    }

    SECTION("setRotation")
    {
        tov::rendering::Transform transform;

        SECTION("sets the transform's rotation to given quaternion")
        {
            auto newRotation = tov::math::Quaternion(tov::math::Radian(tov::math::PI), tov::math::Vector3::UNIT_Z);
            transform.setRotation(newRotation);

            auto rotation = transform.getRotationQuaternion();
            REQUIRE(rotation == newRotation);
        }
    }

    SECTION("getRotationQuaternion")
    {
        tov::rendering::Transform transform;
        auto newRotation = tov::math::Quaternion(tov::math::Radian(tov::math::PI), tov::math::Vector3::UNIT_Z);
        transform.setRotation(newRotation);

        SECTION("returns the transform's rotation as a quaternion")
        {
            auto rotation = transform.getRotationQuaternion();
            REQUIRE(rotation == newRotation);
        }
    }

    SECTION("scale")
    {
        tov::rendering::Transform transform;

        SECTION("scales the transform by the given vector")
        {
            auto initialScale = transform.getScale();
            auto newScale = tov::math::Vector3(2.0f, 2.0f, 2.0f);
            transform.scale(newScale);

            auto scale = transform.getScale();
            REQUIRE(scale == initialScale * newScale);
        }
    }

    SECTION("setScale")
    {
        tov::rendering::Transform transform;

        SECTION("sets the transform's rotation to given quaternion")
        {
            auto newScale = tov::math::Vector3(2.0f, 2.0f, 2.0f);
            transform.setScale(newScale);

            auto scale = transform.getScale();
            REQUIRE(scale == newScale);
        }
    }

    SECTION("getScale")
    {
        tov::rendering::Transform transform;
        auto expectedScale = tov::math::Vector3(2.0f, 2.0f, 2.0f);
        transform.setScale(expectedScale);

        SECTION("returns the transform's scale")
        {
            auto scale = transform.getScale();
            REQUIRE(scale == expectedScale);
        }
    }

    SECTION("getRotationMatrix")
    {
        tov::rendering::Transform transform;
        auto translation = tov::math::Vector3(1.0f, 1.0f, 1.0f);
        transform.setTranslation(translation);
        tov::math::Radian r(tov::math::PI);
        auto rotation = tov::math::Quaternion(r, tov::math::Vector3::UNIT_Z);
        transform.setRotation(rotation);
        auto scale = tov::math::Vector3(1.0f, 2.0f, 3.0f);
        transform.setScale(scale);

        SECTION("returns the transform's rotation as a matrix")
        {
            auto m = transform.getRotationMatrix();
            REQUIRE(cmpf(m[0][0],  tov::math::cos(r)));
            REQUIRE(cmpf(m[0][1], -tov::math::sin(r)));
            REQUIRE(cmpf(m[0][2],  0.0f));
            REQUIRE(cmpf(m[1][0],  tov::math::sin(r)));
            REQUIRE(cmpf(m[1][1],  tov::math::cos(r)));
            REQUIRE(cmpf(m[1][2],  0.0f));
            REQUIRE(cmpf(m[2][0],  0.0f));
            REQUIRE(cmpf(m[2][1],  0.0f));
            REQUIRE(cmpf(m[2][2],  1.0f));
        }
    }

    SECTION("getScaleMatrix")
    {
        tov::rendering::Transform transform;
        auto translation = tov::math::Vector3(1.0f, 1.0f, 1.0f);
        transform.setTranslation(translation);
        tov::math::Radian r(tov::math::PI);
        auto rotation = tov::math::Quaternion(r, tov::math::Vector3::UNIT_Z);
        transform.setRotation(rotation);
        auto scale = tov::math::Vector3(1.0f, 2.0f, 3.0f);
        transform.setScale(scale);

        SECTION("returns the transform's scale as a matrix")
        {
            auto m = transform.getScaleMatrix();
            REQUIRE(cmpf(m[0][0], 1.0f));
            REQUIRE(cmpf(m[0][1], 0.0f));
            REQUIRE(cmpf(m[0][2], 0.0f));
            REQUIRE(cmpf(m[1][0], 0.0f));
            REQUIRE(cmpf(m[1][1], 2.0f));
            REQUIRE(cmpf(m[1][2], 0.0f));
            REQUIRE(cmpf(m[2][0], 0.0f));
            REQUIRE(cmpf(m[2][1], 0.0f));
            REQUIRE(cmpf(m[2][2], 3.0f));
        }
    }

    SECTION("getHomogeneousMatrix")
    {
        tov::rendering::Transform transform;
        auto translation = tov::math::Vector3(1.0f, 2.0f, 3.0f);
        transform.setTranslation(translation);
        tov::math::Radian r(tov::math::PI);
        auto rotation = tov::math::Quaternion(r, tov::math::Vector3::UNIT_Z);
        transform.setRotation(rotation);
        auto scale = tov::math::Vector3(1.0f, 2.0f, 3.0f);
        transform.setScale(scale);

        SECTION("returns the transform as a matrix")
        {
            auto m = transform.getHomogeneousMatrix();
            REQUIRE(cmpf(m[0][0],  scale.x * tov::math::cos(r)));
            REQUIRE(cmpf(m[0][1], -scale.x * tov::math::sin(r)));
            REQUIRE(cmpf(m[0][2],  0.0f));
            REQUIRE(cmpf(m[0][3],  translation.x));
            REQUIRE(cmpf(m[1][0],  scale.y * tov::math::sin(r)));
            REQUIRE(cmpf(m[1][1],  scale.y * tov::math::cos(r)));
            REQUIRE(cmpf(m[1][2],  0.0f));
            REQUIRE(cmpf(m[1][3],  translation.y));
            REQUIRE(cmpf(m[2][0],  0.0f));
            REQUIRE(cmpf(m[2][1],  0.0f));
            REQUIRE(cmpf(m[2][2],  scale.z));
            REQUIRE(cmpf(m[2][3],  translation.z));
            REQUIRE(cmpf(m[3][0],  0.0f));
            REQUIRE(cmpf(m[3][1],  0.0f));
            REQUIRE(cmpf(m[3][2],  0.0f));
            REQUIRE(cmpf(m[3][3],  1.0f));
        }
    }
}
