#ifndef TOV_MEMORY_MEMORY_ARENA_H
#define TOV_MEMORY_MEMORY_ARENA_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    struct AllocationHeader
    {
        void* originalPtr;
        size_t allocationSize;
    };

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
            auto const size = sizeof(T);
            auto const alignment = alignof(T);
            auto const alignmentSpace =
                size
                + mAlignmentPolicy.determineAlignmentSpace(alignment);
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
        AllocationPolicy mAllocationPolicy;
        AlignmentPolicy mAlignmentPolicy;
        ThreadPolicy mThreadPolicy;
        BoundsCheckingPolicy mBoundsCheckingPolicy;
    };

    TOV_NAMESPACE_END // memory
}

#include "memory_arena.inl"

#endif 
