#ifndef TOV_RENDERING_MESH_SUBMESH_H
#define TOV_RENDERING_MESH_SUBMESH_H

#include <tov/rendering/rendering_core.h>

#include "index_data.h"
#include "vertex_data.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    TOV_NAMESPACE_BEGIN(buffers)

    class VertexBufferObject;
    
    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(geometry)
    
    class Geometry;
    
    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_BEGIN(pipeline)

    class Program;

    TOV_NAMESPACE_END // pipeline

    TOV_NAMESPACE_BEGIN(mesh)

    class Mesh;

    class Submesh
    {
        TOV_MOVABLE_ONLY(Submesh)

    public:
        Submesh(Mesh& parentMesh, const geometry::Geometry& geometry, pipeline::Program& program) noexcept;
        ~Submesh() noexcept = default;

    private:
        void build();
        void buildIndexData();
        void buildVertexData();

    private:
        Mesh& mParentMesh;
        const geometry::Geometry& mGeometry;
        pipeline::Program& mProgram;

        IndexDataUPtr mIndexData;
        VertexDataUPtr mVertexData;
    };

    using SubmeshUPtr = std::unique_ptr<Submesh>;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_SUBMESH_H
