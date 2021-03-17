#ifndef TOV_RENDERING_MESH_MESH_INSTANCE_H
#define TOV_RENDERING_MESH_MESH_INSTANCE_H

#include <tov/rendering/rendering_core.h>

#include "draw_data.h"
#include "submesh_instance.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class MeshInstance
    {
        TOV_MOVABLE_ONLY(MeshInstance)

    public:
        MeshInstance() noexcept = default;
        ~MeshInstance() noexcept = default;

        auto addSubmeshInstance(SubmeshInstance& submeshInstance) -> void;
        auto getSubmeshInstance(uint index) -> SubmeshInstance&;

        auto getDrawDataList() -> std::vector<DrawData> const&;

    private:
        std::vector<SubmeshInstance*> mSubmeshInstanceList;
        std::vector<DrawData> mDrawDataList;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
