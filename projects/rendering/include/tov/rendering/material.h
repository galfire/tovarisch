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

    TOV_NAMESPACE_BEGIN(pipeline)
    class Program;
    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_BEGIN(texture)
    class Texture;
    TOV_NAMESPACE_END // texture



    class Material
    {
        TOV_MOVABLE_ONLY(Material)

    public:
        Material(pipeline::Program& program) noexcept;
        ~Material() noexcept = default;

        void setTextureSlot(texture::Texture const *const texture, uint slot);

        auto getRasterizerStateDescriptor() const { return mRasterizerStateDescriptor; }
        auto getRasterizerStateDescriptor() -> auto& { return mRasterizerStateDescriptor; }

        auto instantiate() -> MaterialInstance&;

    private:
        pipeline::Program& mProgram;

        using TextureList = std::vector<texture::Texture const *>;
        TextureList mTextureList;

        pipeline::RasterizerStateDescriptor mRasterizerStateDescriptor;

        std::vector<std::unique_ptr<MaterialInstance>> mInstances;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
