#include <rendering/mesh/mesh_instance.h>

#include <rendering/mesh/submesh_instance.h>
#include <rendering/material_instance.h>
#include <rendering/pipeline/texture_usage.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    auto MeshInstance::addSubmeshInstance(SubmeshInstance& submeshInstance) -> void
    {
        mSubmeshInstanceList.push_back(&submeshInstance);

        std::vector<pipeline::TextureUsage> textureUsages;
        auto materialInstance = submeshInstance.getMaterialInstance();
        if (materialInstance)
        {
            if (materialInstance->getAlbedoMap())
                textureUsages.emplace_back(materialInstance->getAlbedoMap(), 0);
            if (materialInstance->getNormalMap())
                textureUsages.emplace_back(materialInstance->getNormalMap(), 1);
        }

        auto rsd = materialInstance ?
            materialInstance->getRasterizerStateDescriptor() :
            pipeline::RasterizerStateDescriptor{};

        mDrawDataList.emplace_back(
            submeshInstance.getDrawDataContext(),
            submeshInstance.getIndexBufferObject(),
            textureUsages,
            rsd
        );
    }

    auto MeshInstance::getSubmeshInstance(uint index) -> SubmeshInstance&
    {
        return *mSubmeshInstanceList[index];
    }

    auto MeshInstance::getDrawDataList() -> std::vector<mesh::DrawData> const&
    {
        return mDrawDataList;
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
