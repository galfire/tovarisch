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
        : mFormat(format)
    {
        auto handles = mFormat.getHandles();
        for (auto&& handle : handles)
        {
            auto bufferFormat = mFormat.getVertexBufferFormatForHandle(handle);
            auto buffer = bufferManager.createVertexBuffer(bufferFormat, numVertices);
            auto bufferObject = std::unique_ptr<buffers::VertexBufferObject>(
                new buffers::VertexBufferObject(*buffer, bufferFormat)
                );
            mVBOOwningList.push_back(std::move(bufferObject));
            mVBOList.push_back(mVBOOwningList.back().get());
            mHandleToVBOMap.emplace(handle, mVBOOwningList.back().get());
        }
    }

    VertexData::~VertexData() noexcept
    {}

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END //rendering
}
