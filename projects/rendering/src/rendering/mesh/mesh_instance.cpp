#include <rendering/mesh/mesh_instance.h>

#include <rendering/mesh/submesh_instance.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    MeshInstance::MeshInstance() noexcept
    {}

    auto MeshInstance::addSubmeshInstance(SubmeshInstance submeshInstance) -> void
    {
        mSubmeshInstanceList.push_back(submeshInstance);
    }

    auto MeshInstance::getSubmeshInstance(uint index) -> SubmeshInstance&
    {
        return mSubmeshInstanceList[index];
    }

    auto MeshInstance::buildDrawDataList() -> void
    {
        mDrawDataList.clear();

        for (auto&& submeshInstance : mSubmeshInstanceList)
        {
            auto drawData = DrawData(
                submeshInstance.getIndexBufferObject(),
                submeshInstance.getVertexBufferObjects(),
                submeshInstance.getProgramInstance()
            );
            mDrawDataList.push_back(drawData);
        }
    }

    auto MeshInstance::getDrawDataList() -> DrawDataList const&
    {
        buildDrawDataList();
        return mDrawDataList;
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
