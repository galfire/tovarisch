#ifndef TOV_RENDERING_MESH_DRAW_DATA_H
#define TOV_RENDERING_MESH_DRAW_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/index_buffer_object.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>
#include <tov/rendering/pipeline/rasterizer_state_descriptor.h>
#include <tov/rendering/pipeline/texture_descriptor.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData
    {
    public:
        DrawData(
            buffers::IndexBufferObject const& indexBufferObject, 
            std::vector<buffers::VertexBufferObject*> const& vertexBufferObjects,
            std::vector<pipeline::TextureDescriptor> const textureDescriptors,
            pipeline::RasterizerStateDescriptor rasterizerStateDescriptor
        ) noexcept
            : mIndexBufferObject(indexBufferObject)
            , mVertexBufferObjects(vertexBufferObjects)
            , mTextureDescriptors(textureDescriptors)
            , mRasterizerStateDescriptor(rasterizerStateDescriptor)
        {}

        ~DrawData() noexcept = default;

        auto getIndexBufferObject() const -> auto const& { return mIndexBufferObject; }
        auto getVertexBufferObjects() const -> auto const& { return mVertexBufferObjects; }
        auto getTextureDescriptors() const -> auto const& { return mTextureDescriptors; }
        auto getRasterizerStateDescriptor() const { return mRasterizerStateDescriptor; }

    private:
        buffers::IndexBufferObject const& mIndexBufferObject;
        std::vector<buffers::VertexBufferObject*> const& mVertexBufferObjects;
        std::vector<pipeline::TextureDescriptor> const mTextureDescriptors;
        pipeline::RasterizerStateDescriptor mRasterizerStateDescriptor;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
