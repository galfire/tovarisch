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

    //class SubmeshInstance;

    class MeshInstance
    {
    private:
        using DrawDataList = std::vector<DrawData>;

    public:
        MeshInstance() noexcept;
        ~MeshInstance() noexcept = default;

        auto addSubmeshInstance(SubmeshInstance submeshInstance) -> void;
        auto getSubmeshInstance(uint index) -> SubmeshInstance&;

        auto getDrawDataList() -> DrawDataList const&;

    private:
        auto buildDrawDataList() -> void;

    private:
        using SubmeshInstanceList = std::vector<SubmeshInstance>;
        SubmeshInstanceList mSubmeshInstanceList;

        DrawDataList mDrawDataList;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
