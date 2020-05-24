#ifndef TOV_RENDERING_GEOMETRY_CUBE_H
#define TOV_RENDERING_GEOMETRY_CUBE_H

#include "cuboid.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(geometry)

    class Cube
        : public Cuboid
    {
    public:
        Cube(float dimension) noexcept
            : Cuboid(dimension, dimension, dimension)
        {}

        ~Cube() noexcept = default;
    };

    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_END // rendering
}

#endif
