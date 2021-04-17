#include <rendering/mesh/mesh_instance.h>

#include <rendering/mesh/mesh.h>
#include <rendering/mesh/submesh.h>
#include <rendering/mesh/submesh_instance.h>
#include <rendering/material_instance.h>
#include <rendering/pipeline/texture_usage.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    MeshInstance::MeshInstance(Mesh& parentMesh) noexcept
        : mParentMesh(parentMesh)
    {
        auto submeshes = mParentMesh.getSubmeshes();
        for (auto&& submesh : submeshes)
        {
            auto& submeshInstance = submesh->instantiate();
            addSubmeshInstance(submeshInstance);
        }
    }

    auto MeshInstance::addSubmeshInstance(SubmeshInstance& submeshInstance) -> void
    {
        mSubmeshInstanceList.push_back(&submeshInstance);
        mDrawDataList.push_back(submeshInstance.getDrawData());
    }

    auto MeshInstance::getSubmeshInstance(uint index) -> SubmeshInstance&
    {
        return *mSubmeshInstanceList.at(index);
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
