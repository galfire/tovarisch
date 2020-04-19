#include "rendering/geometry/triangle.h"

#include <tov/math/vector.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(geometry)

    Triangle::Triangle()
        : Geometry()
    {
        this->generateVertices();
        this->generateIndicies();
    }

    void Triangle::generateVertices()
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
    }

    void Triangle::generateIndicies()
    {
        this->addIndices(0, 1, 2);
    }

    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_END // rendering
}