#ifndef TOV_MATH_QUATERNION_H
#define TOV_MATH_QUATERNION_H

#include "math_core.h"

#include "vector.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	class Quaternion
		: public Vector4
	{
	public:
		Quaternion(float w, float x, float y, float z)
			: Vector4(x, y, z, w)
		{}
	};

	TOV_NAMESPACE_END
}

#endif