#ifndef TOV_RENDERING_MESH_SUBMESH_H
#define TOV_RENDERING_MESH_SUBMESH_H

#include <tov/rendering/rendering_core.h>

#include "draw_data.h"
#include "index_data.h"
#include "vertex_data.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class VertexBufferObject;
    
    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(geometry)
    
    class Geometry;
    
    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_BEGIN(mesh)

    class Mesh;

    class Submesh
    {
        TOV_MOVABLE_ONLY(Submesh)

    public:
        Submesh(Mesh& parentMesh, const geometry::Geometry& geometry) noexcept;
        ~Submesh() noexcept = default;

        auto getDrawDataList() const -> auto& { return mDrawDataList; }

        auto getVertexDataFormat() const { return mVertexData->getFormat(); }

    private:
        void build();
        void buildIndexData();
        void buildVertexData();

    private:
        Mesh& mParentMesh;
        const geometry::Geometry& mGeometry;

        IndexDataUPtr mIndexData;
        VertexDataUPtr mVertexData;

        using DrawDataList = std::vector<DrawData>;
        DrawDataList mDrawDataList;
    };

    using SubmeshUPtr = std::unique_ptr<Submesh>;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_SUBMESH_H
