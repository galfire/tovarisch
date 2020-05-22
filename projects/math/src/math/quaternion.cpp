#include "math/quaternion.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(math)

    const Quaternion Quaternion::IDENTITY = Quaternion(Radian(0), Vector3::UNIT_X);

    Quaternion::Quaternion(float w, float x, float y, float z) noexcept
        : Vector4(x, y, z, w)
    {}

    Quaternion::Quaternion(Radian angle, const Vector3& axis) noexcept
        : Vector4(0.0f, 0.0f, 0.0f, 0.0f)
    {
        Vector3 normalizedAxis = axis.normalizedCopy();

        Radian halfAngle = angle * 0.5f;
        this->w = math::cos(halfAngle);
        float sinHalfAngle = math::sin(halfAngle);
        this->x = sinHalfAngle * normalizedAxis.x;
        this->y = sinHalfAngle * normalizedAxis.y;
        this->z = sinHalfAngle * normalizedAxis.z;

        for (int i = 0; i < 4; i++)
        {
            if (std::abs(mArr[i]) <= EPSILON)
            {
                mArr[i] = 0;
            }
        }
    }

    auto Quaternion::rotate(const Vector3& vector) const noexcept -> Vector3
    {
        Vector3 xyz = Vector3(x, y, z);
        Vector3 t = xyz.cross(vector) * 2.0f;
        Vector3 tP = vector + t * w + xyz.cross(t);

        for (int i = 0; i < 3; i++)
        {
            if (std::abs(tP[i]) <= EPSILON)
            {
                tP[i] = 0;
            }
        }

        return tP;
    }

    auto Quaternion::operator * (const Vector3& vector) const noexcept -> Vector3
    {
        return this->rotate(vector);
    }

    auto Quaternion::accumulate(const Quaternion& q) const noexcept -> Quaternion
    {
        return Quaternion
        (
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y + y * q.w + z * q.x - x * q.z,
            w * q.z + z * q.w + x * q.y - y * q.x
        );
    }

    auto Quaternion::operator * (const Quaternion& q) const noexcept -> Quaternion
    {
        return this->accumulate(q);
    }

    auto Quaternion::accumulateAssign(const Quaternion& q) noexcept -> Quaternion&
    {
        Quaternion qR = this->accumulate(q);
        *this = qR;
        return *this;
    }

    auto Quaternion::operator *= (const Quaternion& q) noexcept -> Quaternion&
    {
        return this->accumulateAssign(q);
    }

    auto Quaternion::getAngle() const noexcept -> Radian
    {
        return acos(w) * 2.0f;
    }

    auto Quaternion::getAxis() const noexcept -> Vector3
    {
        if (1 - w * w == 0)
        {
            return Vector3(x, y, z);
        }
        else
        {
            float s = std::sqrt(1 - w * w);
            return Vector3(x / s, y / s, z / s);
        }
    }

    auto Quaternion::toRotationMatrix() const noexcept -> Matrix3
    {
        float fTx = x + x;
        float fTy = y + y;
        float fTz = z + z;
        float fTwx = fTx * w;
        float fTwy = fTy * w;
        float fTwz = fTz * w;
        float fTxx = fTx * x;
        float fTxy = fTy * x;
        float fTxz = fTz * x;
        float fTyy = fTy * y;
        float fTyz = fTz * y;
        float fTzz = fTz * z;

        Matrix3 dest;
        dest[0][0] = 1.0f - (fTyy + fTzz);
        dest[0][1] = fTxy - fTwz;
        dest[0][2] = fTxz + fTwy;
        dest[1][0] = fTxy + fTwz;
        dest[1][1] = 1.0f - (fTxx + fTzz);
        dest[1][2] = fTyz - fTwx;
        dest[2][0] = fTxz - fTwy;
        dest[2][1] = fTyz + fTwx;
        dest[2][2] = 1.0f - (fTxx + fTyy);

        return dest;
    }

    TOV_NAMESPACE_END // math
}
