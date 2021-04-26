#pragma once

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(arena)

    template<
        typename T,
        typename AllocationPolicy
    >
    class TypedMemoryArenaSimple
    {
    public:
        inline TypedMemoryArenaSimple(void* start, void* end)
            : mAllocationPolicy(start, end, SIZE)
        {}

        inline ~TypedMemoryArenaSimple() noexcept = default;

        inline auto allocate() -> void*
        {
            auto const allocation = mAllocationPolicy.allocate();
            if (!allocation)
            {
                throw std::bad_alloc();
            }
            return allocation;
        }

        inline auto deallocate(void* ptr) -> void
        {
            mAllocationPolicy.deallocate(ptr);
        }

        inline auto reset() -> void
        {
            mAllocationPolicy.reset();
        }

    public:
        static constexpr auto SIZE = sizeof(T);

    private:
        AllocationPolicy mAllocationPolicy;
    };

    TOV_NAMESPACE_END // arena
    TOV_NAMESPACE_END // memory
}
