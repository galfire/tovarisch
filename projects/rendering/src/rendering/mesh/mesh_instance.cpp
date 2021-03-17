#include <rendering/mesh/mesh_instance.h>

#include <rendering/mesh/submesh_instance.h>
#include <rendering/material_instance.h>
#include <rendering/pipeline/texture_usage.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    MeshInstance::MeshInstance() noexcept
    {}

    auto MeshInstance::addSubmeshInstance(SubmeshInstance& submeshInstance) -> void
    {
        mSubmeshInstanceList.push_back(&submeshInstance);
    }

    auto MeshInstance::getSubmeshInstance(uint index) -> SubmeshInstance&
    {
        return *mSubmeshInstanceList[index];
    }

    auto MeshInstance::buildDrawDataList() -> void
    {
        mDrawDataList.clear();

        for (auto&& submeshInstance : mSubmeshInstanceList)
        {
            auto materialInstance = submeshInstance->getMaterialInstance();

            std::vector<pipeline::TextureUsage> textureUsages;
            if (materialInstance)
            {
                if (materialInstance->getAlbedoMap())
                    textureUsages.emplace_back(materialInstance->getAlbedoMap(), 0);
                if (materialInstance->getNormalMap())
                    textureUsages.emplace_back(materialInstance->getNormalMap(), 1);
            }

            auto drawData = DrawData(
                submeshInstance->getIndexBufferObject(),
                submeshInstance->getVertexBufferObjects(),
                textureUsages,
                materialInstance->getRasterizerStateDescriptor()
            );
            mDrawDataList.push_back(drawData);
        }
    }

    auto MeshInstance::getDrawDataList() -> std::vector<mesh::DrawData> const&
    {
        buildDrawDataList();
        return mDrawDataList;
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
