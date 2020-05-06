#ifndef TOV_RENDERING_MESH_INDEX_DATA_H
#define TOV_RENDERING_MESH_INDEX_DATA_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferManagerBase;
    class IndexBufferObject;

    TOV_NAMESPACE_END // buffers

    TOV_NAMESPACE_BEGIN(mesh)

    class IndexData
    {
        TOV_MOVABLE_ONLY(IndexData)

    public:
        IndexData(
            buffers::BufferManagerBase& bufferManager,
            uint numIndices
        ) noexcept;
        ~IndexData() noexcept;

        auto getBufferObject() const -> buffers::IndexBufferObject&;

    private:
        std::unique_ptr<buffers::IndexBufferObject> mIndexBufferObject;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
