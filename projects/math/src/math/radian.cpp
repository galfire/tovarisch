#include "math/radian.h"

#include "math/degree.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	Radian::Radian(const Degree& degree)
		: mValue(degree.valueRadians())
	{}

	Radian& Radian::operator = (const Degree& rhs)
	{
		mValue = rhs.valueRadians();
		return *this;
	}

	Radian Radian::operator + (const Degree& rhs) const
	{
		return Radian(mValue + rhs.valueRadians());
	}

	Radian& Radian::operator += (const Degree& rhs)
	{
		mValue += rhs.valueRadians();
		return *this;
	}

	Radian Radian::operator - (const Degree& rhs) const
	{
		return Radian(mValue - rhs.valueRadians());
	}

	Radian& Radian::operator -= (const Degree& rhs)
	{
		mValue -= rhs.valueRadians();
		return *this;
	}

	float Radian::valueDegrees(void) const
	{
		return internal::radiansToDegrees(mValue);
	}

	TOV_NAMESPACE_END
}