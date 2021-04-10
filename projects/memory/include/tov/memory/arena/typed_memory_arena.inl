#include <assert.h>

#include "tov/memory/bounds_check_exception.h"

#include <iostream>

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
    inline TypedMemoryArena<T, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::TypedMemoryArena(void* start, void* end)
        : mAllocationPolicy(start, end, allocationSpace())
    {
    }

    template<
        typename T,
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    inline auto TypedMemoryArena<T, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::allocate() -> void*
    {
        auto const allocation = mAllocationPolicy.allocate();
        if (!allocation)
        {
            throw std::bad_alloc();
        }

        auto p = static_cast<void*>(
            static_cast<byte*>(allocation)
            + sizeof(AllocationHeader)
            + BoundsCheckingPolicy::FRONT_BOUND_SIZE
        );
        auto _alignmentSpace = alignmentSpace();
        auto const userPtr = mAlignmentPolicy.align(ALIGNMENT, SIZE, p, _alignmentSpace);

        {
            auto cursor = static_cast<byte*>(userPtr);
            cursor -= BoundsCheckingPolicy::FRONT_BOUND_SIZE;
            mBoundsCheckingPolicy.signFront(cursor);
        }

        {
            auto cursor = static_cast<byte*>(userPtr);
            cursor += SIZE;
            mBoundsCheckingPolicy.signEnd(cursor);
        }

        {
            auto cursor = static_cast<byte*>(userPtr);
            cursor -= BoundsCheckingPolicy::FRONT_BOUND_SIZE;
            cursor -= sizeof(AllocationHeader);
            auto header = AllocationHeader
            {
                allocation,
                SIZE
            };
            memcpy(cursor, &header, sizeof(AllocationHeader));
        }

        return userPtr;
    }

    template<
        typename T,
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    inline auto TypedMemoryArena<T, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::deallocate(void* ptr) -> void
    {
        checkBounds(ptr);

        auto header = getAllocationHeader(ptr);
        mAllocationPolicy.deallocate(header.originalPtr);
    }

    template<
        typename T,
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    inline auto TypedMemoryArena<T, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::reset() -> void
    {
        mAllocationPolicy.reset();
    }

    template<
        typename T,
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
        inline auto TypedMemoryArena<T, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::checkBounds(void* ptr) const -> void
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
