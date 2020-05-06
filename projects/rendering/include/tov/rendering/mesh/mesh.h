#ifndef TOV_RENDERING_MESH_MESH_H
#define TOV_RENDERING_MESH_MESH_H

#include <tov/rendering/rendering_core.h>

#include "draw_data.h"
#include "mesh_instance.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(geometry)
    
    class Geometry;
    
    TOV_NAMESPACE_END // geometry
    TOV_NAMESPACE_BEGIN(pipeline)

    class Program;

    TOV_NAMESPACE_END // pipeline

    TOV_NAMESPACE_BEGIN(mesh)

    class MeshManager;
    class Submesh;

    class Mesh
    {
        TOV_MOVABLE_ONLY(Mesh)

    public:
        Mesh(MeshManager& manager) noexcept;
        ~Mesh() noexcept;

        void addDrawData(DrawData drawData);

        auto getDrawDataList() const -> auto& { return mDrawDataList; }
        auto getManager() const -> auto const& { return mManager; }

        auto createSubmesh(geometry::Geometry const& geometry, pipeline::Program& program) -> Submesh&;
        auto instantiate() const -> MeshInstance;

    private:
        MeshManager& mManager;

        using SubmeshList = std::vector<std::unique_ptr<Submesh>>;
        SubmeshList mSubmeshes;

        using DrawDataList = std::vector<DrawData>;
        DrawDataList mDrawDataList;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_MESH_H
