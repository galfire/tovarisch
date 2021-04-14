#ifndef TOV_RENDERING_MESH_VERTEX_DATA_FORMAT_H
#define TOV_RENDERING_MESH_VERTEX_DATA_FORMAT_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/vertex_buffer_format.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class VertexDataFormat
    {
    public:
        VertexDataFormat() noexcept {}
        ~VertexDataFormat() noexcept {}

        auto addVertexBufferFormat(buffers::VertexBufferFormat vbf) -> void;

        auto getNumVertexBufferFormats() const { return mVertexBufferFormats.size(); }
        auto getVertexBufferFormats() const { return std::span { mVertexBufferFormats }; }
    
    private:
        std::vector<buffers::VertexBufferFormat> mVertexBufferFormats;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
