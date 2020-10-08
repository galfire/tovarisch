#ifndef TOV_RENDERING_MATERIAL_INSTANCE_H
#define TOV_RENDERING_MATERIAL_INSTANCE_H

#include "rendering_core.h"

#include "pipeline/pipeline_state_descriptor.h"
#include "pipeline/rasterizer_state_descriptor.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Material;
    TOV_NAMESPACE_BEGIN(pipeline)
    class ProgramInstance;
    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_BEGIN(texture)
    class Texture;
    TOV_NAMESPACE_END // texture

    class MaterialInstance
    {
        TOV_MOVABLE_ONLY(MaterialInstance)

    public:
        MaterialInstance(
            Material& parentMaterial,
            pipeline::RasterizerStateDescriptor rasterizerStateDescriptor
        ) noexcept;
        ~MaterialInstance() noexcept = default;

        auto setAlbedoMap(texture::Texture const* const texture) { mTextureAlbedoMap = texture; }
        auto getAlbedoMap() const { return mTextureAlbedoMap; }

        auto setNormalMap(texture::Texture const* const texture) { mTextureNormalMap = texture; }
        auto getNormalMap() const { return mTextureNormalMap; }

        auto getRasterizerStateDescriptor() const { return mRasterizerStateDescriptor; }
        auto getRasterizerStateDescriptor() -> auto& { return mRasterizerStateDescriptor; }

    private:
        texture::Texture const* mTextureAlbedoMap = nullptr;
        texture::Texture const* mTextureNormalMap = nullptr;

        pipeline::RasterizerStateDescriptor mRasterizerStateDescriptor;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
