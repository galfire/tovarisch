#ifndef TOV_RENDERING_COMMANDS_DISPATCH_FUNCTION_H
#define TOV_RENDERING_COMMANDS_DISPATCH_FUNCTION_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(commands)

    using DispatchReturnType = void;
    using DispatchDataType = const void*;
    using DispatchFunction = DispatchReturnType(*)(DispatchDataType);

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}

#endif
