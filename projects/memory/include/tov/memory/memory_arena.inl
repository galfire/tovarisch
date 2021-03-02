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
        const auto requiredSize = size + OVERHEAD_REQUIREMENT;

        const auto alignmentSpace = mAlignmentPolicy.determineAlignmentSpace(alignment);
        auto space = requiredSize + alignmentSpace;

        void* allocation = mAllocationPolicy.allocate(space);

        union
        {
            void* asRaw;
            byte* asByte;
        };
        asRaw = allocation;

        void* p = asByte + POLICY_OFFSET + BoundsCheckingPolicy::FRONT_BOUND_SIZE;
        asRaw = mAlignmentPolicy.align(alignment, requiredSize, p, space);

        void* userPtr = asRaw;


        asByte -= POLICY_OFFSET + BoundsCheckingPolicy::FRONT_BOUND_SIZE;

        ptrdiff_t alignmentOffset = asByte - (byte*)allocation;
        mAlignmentPolicy.writeHeader(asRaw, alignmentSpace, alignmentOffset);

        mBoundsSigner.signFront(asRaw);
        auto allocationSize = mAllocationPolicy.getAllocationSize(allocation);
        asByte += allocationSize - (OVERHEAD_REQUIREMENT + alignmentSpace);
        mBoundsSigner.signEnd(asRaw);

        mThreadPolicy.leave();

        return userPtr;
    }

    template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
    inline void MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::deallocate(void* ptr)
    {
        if (!ptr)
        {
            return;
        }

        mThreadPolicy.enter();

        byte* ptrAsByte = (byte*)ptr;

        byte* headersLocation = (byte*)ptr - (POLICY_OFFSET + BoundsCheckingPolicy::FRONT_BOUND_SIZE);
        
        void* currentLocation = (void*)headersLocation;

        size_t alignmentSpace;
        ptrdiff_t alignmentOffset;
        mAlignmentPolicy.readHeader(currentLocation, alignmentSpace, alignmentOffset);

        void* allocationPtr = headersLocation - alignmentOffset;

        // Check guards
        void* frontGuard = currentLocation;
        assert(mBoundsCheckingPolicy.checkFrontSignature(frontGuard));

        size_t allocationSize = mAllocationPolicy.getAllocationSize(allocationPtr);
        byte* endGuard = ptrAsByte + allocationSize - (OVERHEAD_REQUIREMENT + alignmentSpace);
        assert(mBoundsCheckingPolicy.checkEndSignature(endGuard));

        mAllocationPolicy.deallocate(allocationPtr);

        mThreadPolicy.leave();
    }

    template<typename AllocationPolicy, typename AlignmentPolicy,typename ThreadPolicy, typename BoundsCheckingPolicy>
    inline void MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::reset()
    {
        mAllocationPolicy.reset();
    }

    template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
    inline void MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::checkBounds(void* ptr) const
    {
        byte* ptrAsByte = (byte*)ptr;

        //
        //		ORDER OF HEADERS
        //			1. AlignmentPolicy

        byte* headersLocation = (byte*)ptr - (POLICY_OFFSET + BoundsCheckingPolicy::FRONT_BOUND_SIZE);

        void* currentLocation = (void*)headersLocation;

        size_t alignmentSpace;
        ptrdiff_t alignmentOffset;
        mAlignmentPolicy.readHeader(currentLocation, alignmentSpace, alignmentOffset);

        void* allocationPtr = headersLocation - alignmentOffset;

        // Check guards
        void* frontGuard = currentLocation;
        assert(mBoundsCheckingPolicy.checkFrontSignature(frontGuard));

        size_t allocationSize = mAllocationPolicy.getAllocationSize(allocationPtr);
        byte* endGuard = ptrAsByte + allocationSize - (OVERHEAD_REQUIREMENT + alignmentSpace);
        assert(mBoundsCheckingPolicy.checkEndSignature(endGuard));
    }

    TOV_NAMESPACE_END // memory
}
