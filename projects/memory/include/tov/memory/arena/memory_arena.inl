#include <assert.h>

#include <string.h> // memcpy_s

#include "tov/memory/bounds_check_exception.h"

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
    inline MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::MemoryArena(void* start, void* end) noexcept
        : mAllocationPolicy(start, end)
    {
    }

    template<
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    inline auto MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::allocate(size_t size, size_t alignment) -> void*
    {
        auto const alignmentSpace = 
            size 
            + mAlignmentPolicy.determineAlignmentSpace(alignment);
        auto const allocationSpace =
            alignmentSpace
            + sizeof(AllocationHeader)
            + BoundsCheckingPolicy::TOTAL_BOUND_SIZE;
        auto const allocation = mAllocationPolicy.allocate(allocationSpace);
        if (!allocation)
        {
            throw std::bad_alloc();
        }

        auto p = static_cast<void*>(
            static_cast<byte*>(allocation)
            + sizeof(AllocationHeader)
            + BoundsCheckingPolicy::FRONT_BOUND_SIZE
        );
        auto _alignmentSpace = alignmentSpace;
        auto const userPtr = mAlignmentPolicy.align(alignment, size, p, _alignmentSpace);
        
        {
            auto cursor = static_cast<byte*>(userPtr);
            cursor -= BoundsCheckingPolicy::FRONT_BOUND_SIZE;
            mBoundsCheckingPolicy.signFront(cursor);
        }

        {
            auto cursor = static_cast<byte*>(userPtr);
            cursor += size;
            mBoundsCheckingPolicy.signEnd(cursor);
        }

        {
            auto cursor = static_cast<byte*>(userPtr);
            cursor -= BoundsCheckingPolicy::FRONT_BOUND_SIZE;
            cursor -= sizeof(AllocationHeader);
            auto header = AllocationHeader
            {
                allocation,
                size
            };
            memcpy(cursor, &header, sizeof(AllocationHeader));
        }

        return userPtr;
    }

    template<
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    inline auto MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::deallocate(void* ptr) -> void
    {
        checkBounds(ptr);
        
        auto header = getAllocationHeader(ptr);
        mAllocationPolicy.deallocate(header.originalPtr);
    }

    template<
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    inline auto MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::reset() -> void
    {
        mAllocationPolicy.reset();
    }

    template<
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    inline auto MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::checkBounds(void* ptr) const -> void
    {
        auto header = getAllocationHeader(ptr);
        
        auto frontGuard = static_cast<byte*>(ptr) - BoundsCheckingPolicy::FRONT_BOUND_SIZE;
        if (!mBoundsCheckingPolicy.checkFrontSignature(frontGuard))
            throw BoundsCheckException("Front bound signature check failed.");

        auto endGuard = static_cast<byte*>(ptr) + header.allocationSize;
        if (!mBoundsCheckingPolicy.checkEndSignature(endGuard))
            throw BoundsCheckException("End bound signature check failed.");
    }

    TOV_NAMESPACE_END // arena
    TOV_NAMESPACE_END // memory
}
