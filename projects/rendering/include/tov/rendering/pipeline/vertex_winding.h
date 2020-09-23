#ifndef TOV_RENDERING_PIPELINE_VERTEX_WINDING_H
#define TOV_RENDERING_PIPELINE_VERTEX_WINDING_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    enum class VertexWinding
    {
        COUNTERCLOCKWISE,
        CLOCKWISE
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif // TOV_RENDERING_PIPELINE_VERTEX_WINDING_H
