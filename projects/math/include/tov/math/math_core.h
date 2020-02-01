#ifndef TOV_MATH_MATH_CORE_H
#define TOV_MATH_MATH_CORE_H

#include <tov/core.h>

#include <cmath>

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)
	TOV_NAMESPACE_BEGIN(internal)
	
	static const float PI = 4.0f * (float)std::atan(1.0f);

	const float DEG_TO_RAD = PI / 180.0f;
	const float RAD_TO_DEG = 180.0f / PI;

	inline float degreesToRadians(float degrees)
	{
		return degrees * DEG_TO_RAD;
	}

	inline float radiansToDegrees(float radians)
	{
		return radians * RAD_TO_DEG;
	}
	
	TOV_NAMESPACE_END // internal

	static const float PI = internal::PI;

	TOV_NAMESPACE_END // math
}

#endif