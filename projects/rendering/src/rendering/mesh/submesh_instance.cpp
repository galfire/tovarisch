#include <rendering/mesh/submesh_instance.h>

#include <rendering/material_instance.h>
#include <rendering/pipeline/texture_usage.h>


namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    SubmeshInstance::SubmeshInstance(
        DrawDataContext const& drawDataContext,
        buffers::IndexBufferObject ibo,
        MaterialInstance* materialInstance
    )
        : mDrawDataContext(drawDataContext)
        , mIBO(ibo)
        , mMaterialInstance(materialInstance)
    {
        std::vector<pipeline::TextureUsage> textureUsages;
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

        mDrawData = std::make_unique<DrawData>(drawDataContext, ibo, textureUsages, rsd);
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
