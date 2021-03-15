#ifndef TOV_RENDERING_COMMANDS_COMMAND_BUCKET_H
#define TOV_RENDERING_COMMANDS_COMMAND_BUCKET_H

#include <tov/rendering/rendering_core.h>

#include "command_packet.h"

#include <tov/memory_config.h>
#include <tov/memory/heap_area.h>

#include <array>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(commands)

    template <uint Size>
    class CommandBucket
    {
        template <class Command>
        struct Layout
        {
            CommandPacket packet;
            Command command;
        };

    public:
        CommandBucket() noexcept
            : mHeapArea(1_kb * Size)
            , mArena(mHeapArea.getStart(), mHeapArea.getEnd())
        {}

        ~CommandBucket() noexcept = default;

        template <class Command>
        auto addCommand() -> auto&
        {
            auto memory = this->mArena.allocate(sizeof(Layout<Command>), alignof(Layout<Command>));
            auto layout = new (memory) Layout<Command>;
            auto& packet = layout->packet;
            packet.setCommand(&layout->command);
            packet.setDispatchFunction(&Command::DispatchFunction);

            {
                // TODO: synchronization
                auto i = this->mCurrent++;
                this->mCommandPackets[i] = &packet;
            }

            auto command = static_cast<Command*>(packet.getCommand());
            return *command;
        }

        void submit()
        {
            for (auto i = 0u; i < this->mCurrent; i++)
            {
                auto packet = this->mCommandPackets[i];
                packet->submit();
            }

            this->reset();
        }

    private:
        void reset()
        {
            this->mCurrent = 0;
            this->mArena.reset();
        }

    private:
        memory::HeapArea mHeapArea;
        memory::ArenaLinear mArena;

        std::array<CommandPacket*, Size> mCommandPackets = {};
        uint mCurrent = 0;
    };

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}

#endif
