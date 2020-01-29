#include "math/degree.h"

#include "math/radian.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	Degree::Degree(const Radian& radian)
		: mValue(radian.valueDegrees())
	{}

	Degree& Degree::operator = (const Radian& rhs)
	{
		mValue = rhs.valueDegrees();
		return *this;
	}

	Degree Degree::operator + (const Radian& rhs) const
	{
		return Degree(mValue + rhs.valueDegrees());
	}

	Degree& Degree::operator += (const Radian& rhs)
	{
		mValue += rhs.valueDegrees();
		return *this;
	}

	Degree Degree::operator - (const Radian& rhs) const
	{
		return Degree(mValue - rhs.valueDegrees());
	}

	Degree& Degree::operator -= (const Radian& rhs)
	{
		mValue -= rhs.valueDegrees();
		return *this;
	}

	float Degree::valueRadians() const
	{
		return internal::degreesToRadians(mValue);
	}

	TOV_NAMESPACE_END // math
}