#ifndef TOV_MATH_RADIAN_H
#define TOV_MATH_RADIAN_H

#include "math_core.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(math)

    class Degree;

    class Radian
    {
    public:
        Radian(float value = 0.0f)
            : mValue(value)
        {}

        Radian& operator = (float f)
        {
            mValue = f;
            return *this;
        }

        Radian& operator = (const Radian& rhs)
        {
            mValue = rhs.mValue;
            return *this;
        }

        Radian operator + () const
        {
            return *this;
        }

        Radian operator - () const
        {
            return Radian(-mValue);
        }

        Radian operator + (const Radian& rhs) const
        {
            return Radian(mValue + rhs.mValue);
        }

        Radian& operator += (const Radian& rhs)
        {
            mValue += rhs.mValue;
            return *this;
        }

        Radian operator - (const Radian& rhs) const
        {
            return Radian(mValue - rhs.mValue);
        }

        Radian& operator -= (const Radian& rhs)
        {
            mValue -= rhs.mValue;
            return *this;
        }

        Radian operator * (float f) const
        {
            return Radian(mValue * f);
        }

        Radian operator * (const Radian& rhs) const
        {
            return Radian(mValue * rhs.mValue);
        }

        Radian& operator *= (float f)
        {
            mValue *= f;
            return *this;
        }

        Radian operator / (float f) const
        {
            return Radian(mValue / f);
        }

        Radian operator / (const Radian& rhs) const
        {
            return Radian(mValue / rhs.mValue);
        }

        Radian& operator /= (float f)
        {
            mValue /= f;
            return *this;
        }

        float valueRadians() const
        {
            return mValue;
        }

        bool operator == (const Radian& r) const
        {
            return mValue == r.mValue;
        }

        bool operator != (const Radian& r) const
        {
            return mValue != r.mValue;
        }

        bool operator < (const Radian& r) const
        {
            return mValue < r.mValue;
        }

        bool operator <= (const Radian& r) const
        {
            return mValue <= r.mValue;
        }

        bool operator > (const Radian& r) const
        {
            return mValue > r.mValue;
        }

        bool operator >= (const Radian& r) const
        {
            return mValue >= r.mValue;
        }

        Radian(const Degree& degree);

        Degree toDegree() const;

        float valueDegrees(void) const;

    private:
        float mValue;
    };

    inline Radian operator * (float a, const Radian& b)
    {
        return Radian(a * b.valueRadians());
    }

    inline Radian operator / (float a, const Radian& b)
    {
        return Radian(a / b.valueRadians());
    }

    inline Radian operator "" _rad(long double radians)
    {
        return Radian(static_cast<float>(radians));
    }

    TOV_NAMESPACE_END // math
}

#endif