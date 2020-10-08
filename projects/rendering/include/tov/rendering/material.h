#ifndef TOV_RENDERING_MATERIAL_H
#define TOV_RENDERING_MATERIAL_H

#include "rendering_core.h"

#include "pipeline/pipeline_state_descriptor.h"
#include "pipeline/rasterizer_state_descriptor.h"

#include "material_instance.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    TOV_NAMESPACE_BEGIN(texture)
    class Texture;
    TOV_NAMESPACE_END // texture

    class Material
    {
        TOV_MOVABLE_ONLY(Material)

    public:
        Material() noexcept;
        ~Material() noexcept = default;

        auto getRasterizerStateDescriptor() const { return mRasterizerStateDescriptor; }
        auto getRasterizerStateDescriptor() -> auto& { return mRasterizerStateDescriptor; }

        auto instantiate() -> MaterialInstance&;

        auto setAlbedoMap(texture::Texture const* const texture) { mTextureAlbedoMap = texture; }
        auto getAlbedoMap() const { return mTextureAlbedoMap; }

        auto setNormalMap(texture::Texture const* const texture) { mTextureNormalMap = texture; }
        auto getNormalMap() const { return mTextureNormalMap; }

    private:
        pipeline::RasterizerStateDescriptor mRasterizerStateDescriptor;

        texture::Texture const* mTextureAlbedoMap = nullptr;
        texture::Texture const* mTextureNormalMap = nullptr;

        std::vector<std::unique_ptr<MaterialInstance>> mInstances;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
