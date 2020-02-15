#ifndef TOV_MATH_QUATERNION_H
#define TOV_MATH_QUATERNION_H

#include "math_core.h"

#include "vector.h"
#include "trigonometry.h"
#include "radian.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	class Quaternion
		: public Vector4
	{
	public:
		Quaternion(float w, float x, float y, float z) noexcept
			: Vector4(x, y, z, w)
		{}

		Quaternion(Radian angle, const Vector3& axis) noexcept
			: Vector4(0, 0, 0, 0)
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

		Vector3 rotate(const Vector3& vector) const noexcept;
		Vector3 operator * (const Vector3& vector) const noexcept;

		Quaternion accumulate(const Quaternion& q) const noexcept;
		Quaternion operator * (const Quaternion& q) const noexcept;

		Quaternion& accumulateAssign(const Quaternion& q) noexcept;
		Quaternion& operator *= (const Quaternion& q) noexcept;

		Radian getAngle() const noexcept;
		Vector3 getAxis() const noexcept;

	private:
		constexpr static float EPSILON = 9e-8f;
	};

	TOV_NAMESPACE_END // math
}

#endif