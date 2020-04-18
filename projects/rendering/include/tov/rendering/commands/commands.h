#ifndef TOV_RENDERING_COMMANDS_COMMANDS_H
#define TOV_RENDERING_COMMANDS_COMMANDS_H

#include <tov/rendering/rendering_core.h>

#include "dispatch_function.h"

#include <tov/rendering/backend_dispatch.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Viewport;

    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END //rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(commands)

    struct ApplyViewport
    {
        Viewport* viewport;
        static inline DispatchFunction DispatchFunction = BackendDispatch::ApplyViewport;
    };

    struct Draw
    {
        const mesh::DrawData* drawData;
        static inline DispatchFunction DispatchFunction = BackendDispatch::Draw;
    };

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}

#endif
