#ifndef TOV_RENDERING_MESH_MESH_H
#define TOV_RENDERING_MESH_MESH_H

#include <tov/rendering/rendering_core.h>

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

    class Mesh
    {
        TOV_MOVABLE_ONLY(Mesh)

    public:
        Mesh(MeshManager& manager) noexcept;
        ~Mesh() noexcept = default;

        auto getManager() const -> auto const& { return mManager; }

        auto createSubmesh(const geometry::Geometry& geometry) -> auto&
        {
            auto submesh = SubmeshUPtr(
                new Submesh(*this, geometry)
            );
            mSubmeshes.push_back(std::move(submesh));
            auto ret = mSubmeshes.back().get();
            return *ret;
        }

    private:
        MeshManager& mManager;

        using SubmeshList = std::vector<SubmeshUPtr>;
        SubmeshList mSubmeshes;
    };

    using MeshUPtr = std::unique_ptr<Mesh>;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_MESH_H
