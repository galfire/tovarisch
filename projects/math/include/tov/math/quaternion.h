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

		Vector3 rotate(const Vector3& vector) const noexcept;
		Vector3 operator * (const Vector3& vector) const noexcept;

		Quaternion accumulate(const Quaternion& q) const noexcept;
		Quaternion operator * (const Quaternion& q) const noexcept;

		Quaternion& accumulateAssign(const Quaternion& q) noexcept;
		Quaternion& operator *= (const Quaternion& q) noexcept;

		Radian getAngle() const noexcept;
		Vector3 getAxis() const noexcept;

		Matrix3 toRotationMatrix() const noexcept;

	public:
		static const Quaternion IDENTITY;

	private:
		constexpr static float EPSILON = 9e-8f;
	};

	TOV_NAMESPACE_END // math
}

#endif