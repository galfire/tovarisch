#ifndef TOV_RENDERING_MESH_DRAW_DATA_H
#define TOV_RENDERING_MESH_DRAW_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/buffer_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData
    {
    public:
        DrawData(buffers::BufferObject& indexBufferObject, buffers::BufferObject& vertexBufferObject) noexcept
            : mIndexBufferObject(indexBufferObject)
            , mVertexBufferObject(vertexBufferObject)
        {}

        ~DrawData() noexcept = default;

        auto getIndexBufferObject() const -> auto& { return mIndexBufferObject; }
        auto getVertexBufferObject() const -> auto& { return mVertexBufferObject; }

    private:
        buffers::BufferObject& mIndexBufferObject;
        buffers::BufferObject& mVertexBufferObject;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
