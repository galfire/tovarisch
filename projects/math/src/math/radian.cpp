#include "math/radian.h"

#include "math/degree.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	Radian::Radian(const Degree& degree)
		: mValue(degree.valueRadians())
	{}

	Degree Radian::toDegree() const
	{
		return Degree(valueDegrees());
	}

	float Radian::valueDegrees(void) const
	{
		return internal::radiansToDegrees(mValue);
	}

	TOV_NAMESPACE_END
}