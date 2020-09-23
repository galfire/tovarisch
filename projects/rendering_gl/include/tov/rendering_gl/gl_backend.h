#ifndef TOV_RENDERING_GL_GL_BACKEND_H
#define TOV_RENDERING_GL_GL_BACKEND_H

#include <tov/rendering/pipeline/rasterizer_state_descriptor.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(backend)
    TOV_NAMESPACE_BEGIN(gl)

    void SetRasterizerState(pipeline::RasterizerStateDescriptor rasterizerStateDescriptor);

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}

#endif
