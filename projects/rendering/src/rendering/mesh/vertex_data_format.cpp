#include "rendering/mesh/vertex_data_format.h"

#include "rendering/buffers/vertex_attribute.h"
#include "rendering/buffers/vertex_buffer_format.h"
#include "rendering/buffers/vertex_format.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    const VertexDataFormat VertexDataFormat::DEFAULT = []() -> auto
    {
        buffers::VertexFormat vf;
        vf.addAttribute(buffers::VertexAttribute::POSITION, 0);
        vf.addAttribute(buffers::VertexAttribute::NORMAL, 1);
        vf.addAttribute(buffers::VertexAttribute::COLOUR, 2);
        vf.addAttribute(buffers::VertexAttribute::TEXTURE_COORDINATE, 3);
        buffers::VertexBufferFormat vbf(
            buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
            vf
        );
        VertexDataFormat vdf;
        vdf.mapHandleToFormat(0, vbf);
        return vdf;
    }();

    void VertexDataFormat::mapHandleToFormat(VBOHandle handle, VertexBufferFormat vbf)
    {
        auto format = mHandleToFormatMap.find(handle);
        if (format == mHandleToFormatMap.end())
        {
            mHandles.push_back(handle);
            mHandleToFormatMap.emplace(handle, vbf);
        }
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}