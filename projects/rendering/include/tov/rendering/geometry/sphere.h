#ifndef TOV_RENDERING_GEOMETRY_SPHERE_H
#define TOV_RENDERING_GEOMETRY_SPHERE_H

#include "geometry.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(geometry)

    class Sphere
        : public Geometry
    {
    public:
        Sphere(float radius = 1.0f, uint sectorCount = 36u, uint stackCount = 18u);
        ~Sphere() = default;

    private:
        void set(float radius, uint sectorCount, uint stackCount);
        void generateVertices();
        void generateIndicies();

    private:
        float mRadius;
        uint mSectorCount;
        uint mStackCount;
    };

    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_END // rendering
}

#endif
