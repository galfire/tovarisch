#ifndef TOV_RENDERING_BACKEND_H
#define TOV_RENDERING_BACKEND_H

#include "rendering_core.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Viewport;

    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_BEGIN(pipeline)

    class ProgramState;

    TOV_NAMESPACE_END //pipeline

    TOV_NAMESPACE_BEGIN(backend)

    void ApplyViewport(Viewport const *const viewport);
    void ClearViewport(Viewport const *const viewport);
    void Draw(mesh::DrawData const *const drawData);

    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}

#endif
