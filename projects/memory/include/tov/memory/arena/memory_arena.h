#ifndef TOV_MEMORY_MEMORY_ARENA_H
#define TOV_MEMORY_MEMORY_ARENA_H

#include <tov/core.h>

#include "allocation_header.h"
    
namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(arena)

    template<
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    class MemoryArena
    {
        TOV_MOVABLE_ONLY(MemoryArena)

    public:
        inline MemoryArena() noexcept = default;
        inline MemoryArena(void* start, void* end) noexcept;
        inline ~MemoryArena() noexcept = default;

        inline auto allocate(size_t size, size_t alignment) -> void*;
        inline auto deallocate(void* ptr) -> void;
        inline auto reset() -> void;
        inline auto checkBounds(void* ptr) const -> void;

    private:
        inline auto getAllocationHeader(void* ptr) const -> AllocationHeader
        {
            auto cursor = static_cast<byte*>(ptr);
            cursor -= BoundsCheckingPolicy::FRONT_BOUND_SIZE;
            cursor -= sizeof(AllocationHeader);
            return *reinterpret_cast<AllocationHeader*>(cursor);
        }

    private:
        AllocationPolicy mAllocationPolicy;
        AlignmentPolicy mAlignmentPolicy;
        ThreadPolicy mThreadPolicy;
        BoundsCheckingPolicy mBoundsCheckingPolicy;
    };

    TOV_NAMESPACE_END // arena
    TOV_NAMESPACE_END // memory
}

#include "memory_arena.inl"

#endif 
