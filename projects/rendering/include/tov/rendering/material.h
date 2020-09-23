#ifndef TOV_RENDERING_MATERIAL_H
#define TOV_RENDERING_MATERIAL_H

#include "rendering_core.h"

#include "pipeline/cull_mode.h"
#include "pipeline/pipeline_state_descriptor.h"
#include "pipeline/rasterizer_state_descriptor.h"
#include "pipeline/vertex_winding.h"

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
        Material(pipeline::Program const& program) noexcept;
        ~Material() noexcept = default;

        void setCullingEnabled(bool enabled) { mCullingEnabled = enabled; }
        auto getCullingEnabled() const { return mCullingEnabled; }

        void setCullMode(pipeline::CullMode cullMode) { mCullMode = cullMode; }
        auto getCullMode() const { return mCullMode; }

        void setVertexWinding(pipeline::VertexWinding vertexWinding) { mVertexWinding = vertexWinding; }
        auto getVertexWinding() const { return mVertexWinding; }

        void setTextureSlot(texture::Texture const *const texture, uint slot);

        auto getRasterizerStateDescriptor() const
        {
            auto rasterizerStateDescriptor = pipeline::RasterizerStateDescriptor{};
            rasterizerStateDescriptor.cullingEnabled = mCullingEnabled;
            rasterizerStateDescriptor.cullMode = mCullMode;
            rasterizerStateDescriptor.vertexWinding = mVertexWinding;
            return rasterizerStateDescriptor;
        }

    private:
        pipeline::Program const& mProgram;

        using TextureList = std::vector<texture::Texture const *>;
        TextureList mTextureList;

        bool mCullingEnabled = true;
        pipeline::CullMode mCullMode = pipeline::CullMode::BACK;
        pipeline::VertexWinding mVertexWinding = pipeline::VertexWinding::COUNTERCLOCKWISE;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
