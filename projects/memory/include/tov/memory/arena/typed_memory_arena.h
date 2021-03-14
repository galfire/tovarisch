#ifndef TOV_MEMORY_MEMORY_ARENA_H
#define TOV_MEMORY_MEMORY_ARENA_H

#include <tov/core.h>

#include "allocation_header.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(arena)

    template<
        typename T,
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    class TypedMemoryArena
    {
    public:
        inline TypedMemoryArena(void* start, void* end);
        inline ~TypedMemoryArena() noexcept = default;

        inline auto allocate() -> void*;
        inline auto deallocate(void* ptr) -> void;
        inline auto reset() -> void;
        inline auto checkBounds(void* ptr) const -> void;

    private:
        inline auto alignmentSpace()
        {
            auto const alignmentSpace =
                SIZE
                + mAlignmentPolicy.determineAlignmentSpace(ALIGNMENT);
            return alignmentSpace;
        }

        inline auto allocationSpace()
        {
            auto const allocationSpace =
                alignmentSpace()
                + sizeof(AllocationHeader)
                + BoundsCheckingPolicy::TOTAL_BOUND_SIZE;
            return allocationSpace;
        }

        inline auto getAllocationHeader(void* ptr) const -> AllocationHeader
        {
            auto cursor = static_cast<byte*>(ptr);
            cursor -= BoundsCheckingPolicy::FRONT_BOUND_SIZE;
            cursor -= sizeof(AllocationHeader);
            return *reinterpret_cast<AllocationHeader*>(cursor);
        }

    private:
        static constexpr auto SIZE = sizeof(T);
        static constexpr auto ALIGNMENT = alignof(T);

    private:
        AllocationPolicy mAllocationPolicy;
        AlignmentPolicy mAlignmentPolicy;
        ThreadPolicy mThreadPolicy;
        BoundsCheckingPolicy mBoundsCheckingPolicy;
    };

    TOV_NAMESPACE_END // arena
    TOV_NAMESPACE_END // memory
}

#include "typed_memory_arena.inl"

#endif 
