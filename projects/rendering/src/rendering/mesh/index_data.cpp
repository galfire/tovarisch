#include <rendering/mesh/index_data.h>

#include <rendering/buffers/buffer_manager.h>
#include <rendering/buffers/index_buffer_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    IndexData::IndexData(
        buffers::BufferManagerBase& bufferManager,
        uint numIndices
    ) noexcept
    {
        auto buffer = bufferManager.createIndexBuffer(numIndices);
        mIndexBufferObject = std::make_unique<buffers::IndexBufferObject>(*buffer, numIndices);
    }

    IndexData::~IndexData() noexcept
    {}

    auto IndexData::getBufferObject() const -> buffers::IndexBufferObject&
    {
        auto ibo = mIndexBufferObject.get();
        return *static_cast<buffers::IndexBufferObject*>(ibo);
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
