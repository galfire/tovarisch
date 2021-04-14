#ifndef TOV_RENDERING_MESH_VERTEX_DATA_H
#define TOV_RENDERING_MESH_VERTEX_DATA_H

#include <tov/rendering/rendering_core.h>

#include "vertex_data_format.h"
#include <tov/rendering/buffers/vertex_buffer_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferManagerBase;

    TOV_NAMESPACE_END // buffers

    TOV_NAMESPACE_BEGIN(mesh)

    // Container for vertex buffer objects
    // A submesh can be composed of multiple VBOs, where different VBOs contain different vertex attributes.
    // For example, one VBO can contain POSITION data, while another VBO contains NORMAL data.
    class VertexData
    {
        TOV_MOVABLE_ONLY(VertexData)

    public:
        VertexData(
            buffers::BufferManagerBase& bufferManager,
            VertexDataFormat format,
            uint numVertices
        ) noexcept;
        ~VertexData() noexcept;

        auto getVertexBufferObjects() const { return std::span{ mVertexBufferObjects }; }

    private:
        std::vector<buffers::VertexBufferObject> mVertexBufferObjects;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
