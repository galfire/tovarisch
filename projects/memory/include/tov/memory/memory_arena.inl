#include <assert.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template<
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::MemoryArena(void* start, void* end) noexcept
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
            memcpy_s(cursor, sizeof(AllocationHeader), &header, sizeof(AllocationHeader));
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
        assert(mBoundsCheckingPolicy.checkFrontSignature(frontGuard));
        auto endGuard = static_cast<byte*>(ptr) + header.allocationSize;
        assert(mBoundsCheckingPolicy.checkEndSignature(endGuard));
    }

    //
    //
    //

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
            memcpy_s(cursor, sizeof(AllocationHeader), &header, sizeof(AllocationHeader));
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
        assert(mBoundsCheckingPolicy.checkFrontSignature(frontGuard));
        auto endGuard = static_cast<byte*>(ptr) + header.allocationSize;
        assert(mBoundsCheckingPolicy.checkEndSignature(endGuard));
    }

    TOV_NAMESPACE_END // memory
}
