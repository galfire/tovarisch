#ifndef TOV_RENDERING_PIPELINE_SHADER_TYPE_H
#define TOV_RENDERING_PIPELINE_SHADER_TYPE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    enum class ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_PIPELINE_SHADER_TYPE_H
