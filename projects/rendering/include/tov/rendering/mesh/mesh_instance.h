#ifndef TOV_RENDERING_MESH_MESH_INSTANCE_H
#define TOV_RENDERING_MESH_MESH_INSTANCE_H

#include <tov/rendering/rendering_core.h>

#include "draw_data.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class MeshInstance
    {
    public:
        MeshInstance(std::vector<DrawData> const drawData) noexcept
            : mDrawDataList(drawData)
        {}

        ~MeshInstance() noexcept = default;

        auto getDrawDataList() const -> auto const& { return mDrawDataList; }

    private:
        using DrawDataList = std::vector<DrawData>;
        const DrawDataList mDrawDataList;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
