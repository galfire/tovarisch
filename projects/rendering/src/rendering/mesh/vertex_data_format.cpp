#include "rendering/mesh/vertex_data_format.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    auto VertexDataFormat::addVertexBufferFormat(buffers::VertexBufferFormat vbf) -> void
    {
        mVertexBufferFormats.push_back(vbf);
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
