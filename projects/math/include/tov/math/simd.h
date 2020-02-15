#ifndef TOV_MATH_SIMD_H
#define TOV_MATH_SIMD_H

#include "math_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	struct SIMD
	{
		enum Type
		{
			_NONE,
			_128F
		};
	};

	TOV_NAMESPACE_END // math
}

#endif