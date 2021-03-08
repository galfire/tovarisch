#include <assert.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
    MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::MemoryArena(const void* start, const void* end) noexcept
        : mAllocationPolicy(start, end)
        , mAlignmentPolicy()
        , mBoundsSigner()
    {
    }

    template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
    inline void* MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::allocate(size_t size, size_t alignment)
    {
        auto const requiredSize =
            size
            + sizeof(AllocationHeader)
            + BoundsCheckingPolicy::TOTAL_BOUND_SIZE;

        auto const alignmentSpace = mAlignmentPolicy.determineAlignmentSpace(alignment);
        auto space = requiredSize + alignmentSpace;
        auto const allocation = mAllocationPolicy.allocate(space);

        auto p = static_cast<void*>(
            static_cast<byte*>(allocation)
            + sizeof(AllocationHeader)
            + BoundsCheckingPolicy::FRONT_BOUND_SIZE
            );
        auto const userPtr = mAlignmentPolicy.align(alignment, requiredSize, p, space);
        
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

    template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
    inline void MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::deallocate(void* ptr)
    {
        if (!ptr)
        {
            return;
        }

        checkBounds(ptr);
        
        auto header = getAllocationHeader(ptr);
        mAllocationPolicy.deallocate(header.originalPtr);
    }

    template<typename AllocationPolicy, typename AlignmentPolicy,typename ThreadPolicy, typename BoundsCheckingPolicy>
    inline void MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::reset()
    {
        mAllocationPolicy.reset();
    }

    template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
    void MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::checkBounds(void* ptr) const
    {
        auto header = getAllocationHeader(ptr);

        // Check guards
        auto frontGuard = static_cast<byte*>(ptr) - BoundsCheckingPolicy::FRONT_BOUND_SIZE;
        assert(mBoundsCheckingPolicy.checkFrontSignature(frontGuard));
        auto endGuard = static_cast<byte*>(ptr) + header.allocationSize;
        assert(mBoundsCheckingPolicy.checkEndSignature(endGuard));
    }

    TOV_NAMESPACE_END // memory
}
