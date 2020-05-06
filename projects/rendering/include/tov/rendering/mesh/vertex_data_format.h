#ifndef TOV_RENDERING_MESH_VERTEX_DATA_FORMAT_H
#define TOV_RENDERING_MESH_VERTEX_DATA_FORMAT_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/vertex_attribute.h>
#include <tov/rendering/buffers/vertex_buffer_format.h>

#include <unordered_map>
#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class VertexDataFormat
    {
        using VBOHandle = byte;
        using VertexBufferFormat = rendering::buffers::VertexBufferFormat;
        using HandleToFormatMap = std::unordered_map<VBOHandle, VertexBufferFormat>;
        using HandleList = std::vector<VBOHandle>;
        using VertexBufferFormatList = std::vector<VertexBufferFormat>;

    public:
        VertexDataFormat() noexcept {}
        ~VertexDataFormat() noexcept {}

        void mapHandleToFormat(VBOHandle handle, VertexBufferFormat vbf);

        auto getVertexBufferFormatForHandle(VBOHandle handle) const
        {
            auto format = mHandleToFormatMap.at(handle);
            return format;
        }

        auto getHandles() const -> auto const& { return mHandles; }
        auto getVertexBufferFormats() const -> auto const& { return mVertexBufferFormats; }
    private:
        HandleList mHandles;
        VertexBufferFormatList mVertexBufferFormats;
        HandleToFormatMap mHandleToFormatMap;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
