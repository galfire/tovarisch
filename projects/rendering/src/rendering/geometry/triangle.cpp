#include <rendering/geometry/triangle.h>

#include <tov/math/vector.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(geometry)

    Triangle::Triangle()
        : Geometry()
    {
        // v1
        // | \
        // |  \
        // v3--v2

        const auto length = 5.0f;

        math::Vector3 v1(0.0f, length, 0.0f);
        this->addPosition(v1);

        math::Vector3 v2(length, 0.0f, 0.0f);
        this->addPosition(v2);

        math::Vector3 v3(0.0f, 0.0f, 0.0f);
        this->addPosition(v3);

        // CCW vertex winding
        this->addIndices(0, 2, 1);
    }

    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_END // rendering
}
