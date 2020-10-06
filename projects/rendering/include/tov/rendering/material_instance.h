#ifndef TOV_RENDERING_MATERIAL_INSTANCE_H
#define TOV_RENDERING_MATERIAL_INSTANCE_H

#include "rendering_core.h"

#include "pipeline/pipeline_state_descriptor.h"
#include "pipeline/rasterizer_state_descriptor.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

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
            pipeline::ProgramInstance& programInstance,
            pipeline::RasterizerStateDescriptor rasterizerStateDescriptor
        ) noexcept;
        ~MaterialInstance() noexcept = default;

        auto getProgramInstance() -> auto& { return mProgramInstance; }
        auto getProgramInstance() const -> auto const& { return mProgramInstance; }

        auto getRasterizerStateDescriptor() const { return mRasterizerStateDescriptor; }
        auto getRasterizerStateDescriptor() -> auto& { return mRasterizerStateDescriptor; }

    private:
        pipeline::ProgramInstance& mProgramInstance;

        using TextureList = std::vector<texture::Texture const*>;
        TextureList mTextureList;

        pipeline::RasterizerStateDescriptor mRasterizerStateDescriptor;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
