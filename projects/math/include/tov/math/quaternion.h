#ifndef TOV_MATH_QUATERNION_H
#define TOV_MATH_QUATERNION_H

#include "math_core.h"

#include "matrix.h"
#include "radian.h"
#include "trigonometry.h"
#include "vector.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(math)

    class Quaternion
        : public Vector4
    {
    public:
        Quaternion(float w, float x, float y, float z) noexcept;
        Quaternion(Radian angle, const Vector3& axis) noexcept;

        auto rotate(const Vector3& vector) const noexcept -> Vector3;
        auto operator * (const Vector3& vector) const noexcept -> Vector3;

        auto accumulate(const Quaternion& q) const noexcept -> Quaternion;
        auto operator * (const Quaternion& q) const noexcept -> Quaternion;

        auto accumulateAssign(const Quaternion& q) noexcept -> Quaternion&;
        auto operator *= (const Quaternion& q) noexcept -> Quaternion&;

        auto getAngle() const noexcept -> Radian;
        auto getAxis() const noexcept -> Vector3;

        auto toRotationMatrix() const noexcept -> Matrix3;

    public:
        static const Quaternion IDENTITY;

    private:
        constexpr static float EPSILON = 9e-8f;
    };

    TOV_NAMESPACE_END // math
}

#endif
