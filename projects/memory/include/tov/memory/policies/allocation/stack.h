#pragma once

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
        TOV_NAMESPACE_BEGIN(policies)
        TOV_NAMESPACE_BEGIN(allocation)

        class Stack
    {
    public:
        inline explicit Stack(void* start, void* end, size_t elementSize) noexcept
            : mStart(start)
            , mEnd(end)
            , mElementSize(elementSize)
            , mPosition(static_cast<byte*>(start))
        {
        }

        inline ~Stack() noexcept = default;

        inline auto allocate() noexcept -> void*
        {
            mPosition += mElementSize;
        }

        inline auto deallocate(void* ptr) noexcept -> void
        {
            mPosition -= mElementSize;
        }

        inline auto reset() noexcept -> void
        {
            mPosition = static_cast<byte*>(mStart);
        }

    private:
        void* mStart;
        void* mEnd;
        size_t mElementSize;
        byte* mPosition;
    };

    TOV_NAMESPACE_END // allocation
        TOV_NAMESPACE_END // policies
        TOV_NAMESPACE_END // memory
}
