#include <rendering/geometry/rectangle.h>

#include <tov/math/vector.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(geometry)

    Rectangle::Rectangle(float width, float height) noexcept
        : Geometry()
        , mWidth(width)
        , mHeight(height)
    {
        // Scale position by width and height
        auto const positionScale = math::Vector3(mWidth, mHeight, 1.0f);
        auto const UNIT = 0.5f;

        auto p0 = math::Vector3(-UNIT, +UNIT, 0.0f) * positionScale;
        auto t0 = math::Vector2(0.0f, 1.0f);

        auto p1 = math::Vector3(-UNIT, -UNIT, 0.0f) * positionScale;
        auto t1 = math::Vector2(0.0f, 0.0f);

        auto p2 = math::Vector3(+UNIT, +UNIT, 0.0f) * positionScale;
        auto t2 = math::Vector2(1.0f, 1.0f);

        auto p3 = math::Vector3(+UNIT, -UNIT, 0.0f) * positionScale;
        auto t3 = math::Vector2(1.0f, 0.0f);

        this->addPosition(p0);
        this->addPosition(p1);
        this->addPosition(p2);
        this->addPosition(p3);

        this->addTextureCoordinate(t0);
        this->addTextureCoordinate(t1);
        this->addTextureCoordinate(t2);
        this->addTextureCoordinate(t3);

        // CCW vertex winding
        this->addIndices(0, 1, 2);
        this->addIndices(2, 1, 3);
    }

    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_END // rendering
}
