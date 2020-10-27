#ifndef TOV_RENDERING_MESH_SUBMESH_H
#define TOV_RENDERING_MESH_SUBMESH_H

#include <tov/rendering/rendering_core.h>

#include "submesh_instance.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    TOV_NAMESPACE_BEGIN(buffers)

    class VertexBufferObject;
    
    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(geometry)
    
    class Geometry;
    
    TOV_NAMESPACE_END // geometry

    class Material;

    TOV_NAMESPACE_BEGIN(mesh)

    class IndexData;
    class Mesh;
    class VertexData;
    class VertexDataFormat;

    class Submesh
    {
        TOV_MOVABLE_ONLY(Submesh)

    public:
        Submesh(Mesh& parentMesh, geometry::Geometry const& geometry, VertexDataFormat const& vertexDataFormat) noexcept;
        ~Submesh() noexcept;

        auto getIndexData() const -> auto const& { return mIndexData; }
        auto getVertexData() const -> auto const& { return mVertexData; }

        auto setMaterial(Material& material) -> void { mMaterial = &material; }

        auto instantiate() -> SubmeshInstance&;

    private:
        void build(geometry::Geometry const&, VertexDataFormat const& vertexDataFormat);
        void buildIndexData(geometry::Geometry const& geometry);
        void buildVertexData(geometry::Geometry const& geometry, VertexDataFormat const& vertexDataFormat);

    private:
        Mesh& mParentMesh;

        Material* mMaterial = nullptr;

        std::unique_ptr<IndexData> mIndexData;
        std::unique_ptr<VertexData> mVertexData;

        std::vector<std::unique_ptr<SubmeshInstance>> mSubmeshInstances;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_SUBMESH_H
