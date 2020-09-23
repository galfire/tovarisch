#ifndef TOV_RENDERING_PIPELINE_CULL_MODE_H
#define TOV_RENDERING_PIPELINE_CULL_MODE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    enum class CullMode
    {
        FRONT,
        BACK,
        FRONT_AND_BACK
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif // TOV_RENDERING_PIPELINE_CULL_MODE_H
