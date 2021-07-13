#ifndef TOV_RENDERING_MESH_MESH_H
#define TOV_RENDERING_MESH_MESH_H

#include <tov/rendering/rendering_core.h>

#include <tov/memory/container.h>

#include "mesh_instance.h"
#include "submesh.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(geometry)
    
    class Geometry;
    
    TOV_NAMESPACE_END // geometry

    TOV_NAMESPACE_BEGIN(mesh)

    class MeshManager;
    class Submesh;
    class VertexDataFormat;

    class Mesh
    {
        TOV_MOVABLE_ONLY(Mesh)

    public:
        Mesh(MeshManager& manager) noexcept;
        ~Mesh() noexcept;

        auto getManager() const -> auto const& { return mManager; }

        auto createSubmesh(geometry::Geometry const& geometry, VertexDataFormat const& vertexDataFormat) -> Submesh&;
        auto instantiate() -> MeshInstance&;

        auto getSubmeshes() const { return std::span{ mSubmeshes }; }

    private:
        MeshManager& mManager;

        using SubmeshList = memory::Container<Submesh, 8>;
        SubmeshList mSubmeshes;

        using MeshInstanceList = std::vector<std::unique_ptr<MeshInstance>>;
        MeshInstanceList mMeshInstances;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_MESH_H
