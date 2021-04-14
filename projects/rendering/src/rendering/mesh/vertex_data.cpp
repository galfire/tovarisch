#include <rendering/mesh/vertex_data.h>

#include <rendering/buffers/buffer_manager.h>
#include <rendering/buffers/vertex_buffer_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    VertexData::VertexData(
        buffers::BufferManagerBase& bufferManager,
        VertexDataFormat format,
        uint numVertices
    ) noexcept
    {
        auto bufferFormats = format.getVertexBufferFormats();
        for (auto&& bufferFormat : bufferFormats)
        {
            auto buffer = bufferManager.createVertexBuffer(bufferFormat, numVertices);
            mVertexBufferObjects.emplace_back(*buffer);
        }
    }

    VertexData::~VertexData() noexcept
    {}

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END //rendering
}
