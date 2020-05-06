#ifndef TOV_RENDERING_MESH_SUBMESH_H
#define TOV_RENDERING_MESH_SUBMESH_H

#include <tov/rendering/rendering_core.h>

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

    class IndexData;
    class Mesh;
    class VertexData;

    class Submesh
    {
        TOV_MOVABLE_ONLY(Submesh)

    public:
        Submesh(Mesh& parentMesh, const geometry::Geometry& geometry, pipeline::Program& program) noexcept;
        ~Submesh() noexcept;

    private:
        void build();
        void buildIndexData();
        void buildVertexData();

    private:
        Mesh& mParentMesh;
        const geometry::Geometry& mGeometry;
        pipeline::Program& mProgram;

        std::unique_ptr<IndexData> mIndexData;
        std::unique_ptr<VertexData> mVertexData;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_SUBMESH_H
