#ifndef TOV_RENDERING_MESH_INDEX_DATA_H
#define TOV_RENDERING_MESH_INDEX_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/buffer_manager.h>
#include <tov/rendering/buffers/buffer_object.h>
#include <tov/rendering/buffers/index_buffer_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class IndexData
    {
        TOV_MOVABLE_ONLY(IndexData)

    public:
        IndexData(
            buffers::BufferManagerBase& bufferManager,
            uint numIndices
        ) noexcept
        {
            auto buffer = bufferManager.createIndexBuffer(numIndices);
            auto bufferObject = buffers::BufferObjectUPtr(
                new buffers::IndexBufferObject(*buffer, numIndices)
            );
            mIndexBufferObject = std::move(bufferObject);
        }

        ~IndexData() noexcept = default;

        auto getBufferObject() const
        {
            auto ibo = mIndexBufferObject.get();
            return static_cast<buffers::IndexBufferObject*>(ibo);
        }

    private:
        buffers::BufferObjectUPtr mIndexBufferObject;
    };

    using IndexDataUPtr = std::unique_ptr<IndexData>;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
