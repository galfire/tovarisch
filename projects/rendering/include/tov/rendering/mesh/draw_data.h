#ifndef TOV_RENDERING_MESH_DRAW_DATA_H
#define TOV_RENDERING_MESH_DRAW_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/index_buffer_object.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>
#include <tov/rendering/pipeline/rasterizer_state_descriptor.h>
#include <tov/rendering/pipeline/texture_usage.h>

#include <tov/rendering/mesh/draw_data_context.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData
    {
    public:
        DrawData(
            mesh::DrawDataContext const& drawDataContext,
            buffers::IndexBufferObject const& indexBufferObject, 
            std::vector<pipeline::TextureUsage> const textureUsages,
            pipeline::RasterizerStateDescriptor rasterizerStateDescriptor
        ) noexcept
            : mDrawDataContext(drawDataContext)
            , mIndexBufferObject(indexBufferObject)
            , mTextureUsages(textureUsages)
            , mRasterizerStateDescriptor(rasterizerStateDescriptor)
        {}
        ~DrawData() noexcept = default;

        auto getDrawDataContext() const -> auto const& { return mDrawDataContext; }
        auto getIndexBufferObject() const -> auto const& { return mIndexBufferObject; }
        auto getTextureUsages() const -> auto const& { return mTextureUsages; }
        auto getRasterizerStateDescriptor() const { return mRasterizerStateDescriptor; }

    private:
        mesh::DrawDataContext const& mDrawDataContext;
        buffers::IndexBufferObject const& mIndexBufferObject;
        std::vector<pipeline::TextureUsage> const mTextureUsages;
        pipeline::RasterizerStateDescriptor mRasterizerStateDescriptor;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
