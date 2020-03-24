#ifndef TOV_RENDERING_BACKEND_H
#define TOV_RENDERING_BACKEND_H

#include "rendering_core.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Viewport;

    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(backend)

    void ApplyViewport(Viewport* viewport);

    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}

#endif
