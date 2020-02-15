#ifndef TOV_MATH_PLANE_H
#define TOV_MATH_PLANE_H

#include "math_core.h"

#include "vector.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	class Plane
	{
	public:
		Plane() noexcept = default;
		Plane(const Vector3& normal, float constant) noexcept;
		Plane(float a, float b, float c, float d) noexcept;

		float getDistance(const Vector3& point) const noexcept;

		const Vector3& getNormal() const { return mNormal; }
		float getD() const { return mD; }

	private:
		Vector3 mNormal = Vector3::ZERO;
		float mD = 0;
	};

	TOV_NAMESPACE_END // math
}

#endif