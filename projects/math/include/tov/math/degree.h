#ifndef TOV_MATH_DEGREE_H
#define TOV_MATH_DEGREE_H

#include "math_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	class Radian;

	class Degree
	{
	public:
		explicit Degree(float value)
			: mValue(value)
		{}


		float valueDegrees(void) const
		{
			return mValue;
		}

		Degree& operator = (const Degree& d)
		{
			mValue = d.mValue;
			return *this;
		}

		Degree operator + () const
		{
			return *this;
		}

		Degree operator - () const
		{
			return Degree(-mValue);
		}

		Degree operator + (const Degree& rhs) const
		{
			return Degree(mValue + rhs.mValue);
		}

		Degree& operator += (const Degree& rhs)
		{
			mValue += rhs.mValue;
			return *this;
		}

		Degree operator - (const Degree& rhs) const
		{
			return Degree(mValue - rhs.mValue);
		}

		Degree& operator -= (const Degree& rhs)
		{
			mValue -= rhs.mValue;
			return *this;
		}

		Degree operator * (float f) const
		{
			return Degree(mValue * f);
		}

		Degree& operator *= (float f)
		{
			mValue *= f;
			return *this;
		}

		Degree operator / (float f) const
		{
			return Degree(mValue / f);
		}

		Degree& operator /= (float f)
		{
			mValue /= f;
			return *this;
		}

		bool operator == (const Degree& r) const
		{
			return mValue == r.mValue;
		}

		bool operator != (const Degree& r) const
		{
			return mValue != r.mValue;
		}

		bool operator < (const Degree& r) const
		{
			return mValue < r.mValue;
		}

		bool operator <= (const Degree& r) const
		{
			return mValue <= r.mValue;
		}

		bool operator > (const Degree& r) const
		{
			return mValue > r.mValue;
		}

		bool operator >= (const Degree& r) const
		{
			return mValue >= r.mValue;
		}

		Degree(const Radian& radian);

		Radian toRadian() const;

		float valueRadians(void) const;

	private:
		float mValue;
	};

	inline Degree operator "" _deg(long double degrees)
	{
		return Degree(static_cast<float>(degrees));
	}

	TOV_NAMESPACE_END
}

#endif