#ifndef TOV_MATH_TRIGONOMETRY_H
#define TOV_MATH_TRIGONOMETRY_H

#include "math_core.h"

#include "radian.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(math)

    inline float tan(const Radian& value) { return (float)std::tan(value.valueRadians()); }
    inline float sin(const Radian& value) { return (float)std::sin(value.valueRadians()); }
    inline float cos(const Radian& value) { return (float)std::cos(value.valueRadians()); }

    inline Radian atan(float fValue) { return Radian(std::atan(fValue)); }
    inline Radian asin(float fValue) { return Radian(std::asin(fValue)); }
    inline Radian acos(float fValue) { return Radian(std::acos(fValue)); }

    TOV_NAMESPACE_END
}

#endif
