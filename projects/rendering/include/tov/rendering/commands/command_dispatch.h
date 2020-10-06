#ifndef TOV_RENDERING_COMMANDS_COMMAND_DISPATCH_H
#define TOV_RENDERING_COMMANDS_COMMAND_DISPATCH_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(commands)

    class CommandDispatch
    {
    public:
        static void ApplyViewport(const void* data);
        static void ClearViewport(const void* data);
        static void Draw(const void* data);

        static void StartDrawDataContext(const void* data);
        static void EndDrawDataContext(const void* data);
    };

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}

#endif
