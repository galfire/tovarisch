#include "math/quaternion.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	Vector3 Quaternion::rotate(const Vector3& vector) const noexcept
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

	Vector3 Quaternion::operator * (const Vector3& vector) const noexcept
	{
		return this->rotate(vector);
	}

	Quaternion Quaternion::accumulate(const Quaternion& q) const noexcept
	{
		return Quaternion
		(
			w * q.w - x * q.x - y * q.y - z * q.z,
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y + y * q.w + z * q.x - x * q.z,
			w * q.z + z * q.w + x * q.y - y * q.x
		);
	}

	Quaternion Quaternion::operator * (const Quaternion& q) const noexcept
	{
		return this->accumulate(q);
	}

	Quaternion& Quaternion::accumulateAssign(const Quaternion& q) noexcept
	{
		Quaternion qR = this->accumulate(q);
		*this = qR;
		return *this;
	}

	Quaternion& Quaternion::operator *= (const Quaternion& q) noexcept
	{
		return this->accumulateAssign(q);
	}

	Radian Quaternion::getAngle() const noexcept
	{
		return acos(w) * 2.0f;
	}

	Vector3 Quaternion::getAxis() const noexcept
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

	TOV_NAMESPACE_END // math
}
