#include "rendering/mesh/vertex_data_format.h"

#include "rendering/buffers/vertex_attribute.h"
#include "rendering/buffers/vertex_buffer_format.h"
#include "rendering/buffers/vertex_format.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    void VertexDataFormat::mapHandleToFormat(VBOHandle handle, VertexBufferFormat vbf)
    {
        auto format = mHandleToFormatMap.find(handle);
        if (format == mHandleToFormatMap.end())
        {
            mHandles.push_back(handle);
            mVertexBufferFormats.push_back(vbf);
            mHandleToFormatMap.emplace(handle, vbf);
        }
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
