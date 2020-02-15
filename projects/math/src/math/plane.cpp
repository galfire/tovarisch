#include "math/plane.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	Plane::Plane(const Vector3& normal, float constant) noexcept
		: mNormal(normal)
		, mD(-constant)
	{}

	Plane::Plane(float a, float b, float c, float d) noexcept
		: mNormal(a, b, c)
		, mD(d)
	{}

	float Plane::getDistance(const Vector3& point) const noexcept
	{
		return mNormal.dot(point) + mD;
	}

	TOV_NAMESPACE_END // math
}