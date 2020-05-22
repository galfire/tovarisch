#include "math/degree.h"

#include "math/radian.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(math)

    Degree::Degree(const Radian& radian)
        : mValue(radian.valueDegrees())
    {}

    Radian Degree::toRadian() const
    {
        return Radian(valueRadians());
    }

    float Degree::valueRadians() const
    {
        return internal::degreesToRadians(mValue);
    }

    TOV_NAMESPACE_END // math
}
