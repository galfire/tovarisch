#ifndef TOV_RENDERING_GEOMETRY_GEOMETRY_H
#define TOV_RENDERING_GEOMETRY_GEOMETRY_H

#include <tov/rendering/rendering_core.h>

#include <tov/math/vector.h>

#include <tov/rendering/buffers/vertex_attribute.h>

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(geometry)

    class Geometry
    {
    public:
        Geometry() noexcept = default;
        virtual ~Geometry() noexcept = default;

        auto getNumVertices() const { return mPositions.size(); }
        auto getNumPositions() const { return mPositions.size(); }
        auto getNumNormals() const { return mNormals.size(); }
        auto getNumTextureCoordinates() const { return mTextureCoordinates.size(); }
        auto getNumIndices() const { return mIndices.size(); }

        auto hasPositions() const { return this->getNumPositions() > 0; }
        auto hasNormals() const { return this->getNumNormals() > 0; }
        auto hasTextureCoordinates() const { return this->getNumTextureCoordinates() > 0; }

        auto hasAttribute(buffers::VertexAttribute attribute) const
        {
            switch (attribute.getSemantic())
            {
            case buffers::VertexAttribute::Semantic::POSITION:
                return this->hasPositions();
            case buffers::VertexAttribute::Semantic::NORMAL:
                return this->hasNormals();
            case buffers::VertexAttribute::Semantic::TEXTURE_COORDINATE:
                return this->hasTextureCoordinates();
            default:
                return false;
            }
        }

        auto getPositions() const -> auto const { return mPositions.data(); }
        auto getNormals() const -> auto const { return mNormals.data(); }
        auto getTextureCoordinates() const -> auto const { return mTextureCoordinates.data(); }
        auto getIndices() const -> auto const { return mIndices.data(); }

    protected:
        void addPosition(math::Vector3 position) { mPositions.push_back(position); }
        void addNormal(math::Vector3 normal) { mNormals.push_back(normal); }
        void addTextureCoordinate(math::Vector2 textureCoordinate) { mTextureCoordinates.push_back(textureCoordinate); }
        void addIndices(int i1, int i2, int i3)
        {
            mIndices.push_back(i1);
            mIndices.push_back(i2);
            mIndices.push_back(i3);
        }

    private:
        std::vector<math::Vector3> mPositions;
        std::vector<math::Vector3> mNormals;
        std::vector<math::Vector2> mTextureCoordinates;
        std::vector<int> mIndices;
    };

    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_END // rendering
}

#endif
