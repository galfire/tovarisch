#ifndef TOV_RENDERING_BACKEND_H
#define TOV_RENDERING_BACKEND_H

#include "rendering_core.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Viewport;

    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(backend)

    void ApplyViewport(Viewport* viewport);
    void Draw(const mesh::DrawData* drawData);

    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}

#endif
