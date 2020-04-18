#ifndef TOV_RENDERING_MESH_VERTEX_DATA_H
#define TOV_RENDERING_MESH_VERTEX_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/buffer_manager.h>
#include <tov/rendering/buffers/buffer_object.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>

#include "vertex_data_format.h"

#include <functional>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    // Container for vertex buffer objects
    // A submesh can be composed of multiple VBOs, where different VBOs contain different vertex attributes.
    // For example, one VBO can contain POSITION data, while another VBO contains NORMAL data.
    class VertexData
    {
        TOV_MOVABLE_ONLY(VertexData)

        using VBOHandle =       byte;
        using VBOOwningList =   std::vector<buffers::BufferObjectUPtr>;
        using VBOList =         std::vector<buffers::BufferObject*>;
        using HandleToVBOMap =  std::unordered_map<VBOHandle, buffers::BufferObject*>;

    public:
        VertexData(
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
                auto bufferObject = buffers::BufferObjectUPtr(
                    new buffers::VertexBufferObject(*buffer, bufferFormat)
                );
                mVBOOwningList.push_back(std::move(bufferObject));
                mVBOList.push_back(mVBOOwningList.back().get());
                mHandleToVBOMap.emplace(handle, mVBOOwningList.back().get());
            }
        }

        ~VertexData() noexcept = default;

        auto getBufferObjectForHandle(VBOHandle handle) const
        {
            auto vbo = mHandleToVBOMap.at(handle);
            return static_cast<buffers::VertexBufferObject*>(vbo);
        }

        auto getBufferObjects() const -> auto&
        {
            return mVBOList;
        }

        auto getFormat() const -> auto& { return mFormat; }

    private:
        VertexDataFormat mFormat;
        VBOOwningList mVBOOwningList;
        VBOList mVBOList;
        HandleToVBOMap mHandleToVBOMap;
    };

    using VertexDataUPtr = std::unique_ptr<VertexData>;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
