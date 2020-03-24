#ifndef TOV_RENDERING_COMMANDS_COMMAND_PACKET_H
#define TOV_RENDERING_COMMANDS_COMMAND_PACKET_H

#include <tov/rendering/rendering_core.h>

#include "dispatch_function.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(commands)

    class CommandPacket
    {
    public:
        CommandPacket() noexcept = default;
        ~CommandPacket() noexcept = default;

        auto getDispatchFunction() const { return mDispatchFunction; }
        auto getCommand() const { return mCommand; }

    private:
        template <uint Size> friend class CommandBucket;

        template<class U>
        void setCommand(U* command)
        {
            mCommand = (void*)command;
        }

        void setDispatchFunction(DispatchFunction* dispatchFunction)
        {
            mDispatchFunction = dispatchFunction;
        }

        void submit()
        {
            (*mDispatchFunction)(mCommand);
        }

    private:
        void* mCommand;
        DispatchFunction* mDispatchFunction;
    };

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}

#endif
