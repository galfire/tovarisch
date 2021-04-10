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
        auto handles = format.getHandles();
        for (auto&& handle : handles)
        {
            {
                auto bufferFormat = format.getVertexBufferFormatForHandle(handle);
                auto buffer = bufferManager.createVertexBuffer(bufferFormat, numVertices);
                auto bufferObject = std::make_unique<buffers::VertexBufferObject>(*buffer);
                mVertexBufferObjects.push_back(std::move(bufferObject));
            }
            mHandleToVBOMap.emplace(handle, mVertexBufferObjects.back().get());
        }
    }

    VertexData::~VertexData() noexcept
    {}

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END //rendering
}
