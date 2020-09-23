#ifndef TOV_RENDERING_PIPELINE_RASTERIZER_STATE_DESCRIPTOR_H
#define TOV_RENDERING_PIPELINE_RASTERIZER_STATE_DESCRIPTOR_H

#include <tov/rendering/rendering_core.h>

#include "cull_mode.h"
#include "vertex_winding.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    struct RasterizerStateDescriptor
    {
        bool cullingEnabled = true;
        CullMode cullMode = CullMode::BACK;
        VertexWinding vertexWinding = VertexWinding::COUNTERCLOCKWISE;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
