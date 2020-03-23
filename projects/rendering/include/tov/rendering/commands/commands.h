#ifndef TOV_RENDERING_COMMANDS_COMMANDS_H
#define TOV_RENDERING_COMMANDS_COMMANDS_H

#include <tov/rendering/rendering_core.h>

#include "dispatch_function.h"

#include <tov/rendering/backend_dispatch.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)


    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(commands)

    struct ApplyViewport
    {
        int i = 0;
        static inline DispatchFunction DispatchFunction = BackendDispatch::ApplyViewport;
    };

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}

#endif
