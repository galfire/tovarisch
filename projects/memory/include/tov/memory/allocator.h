#pragma once

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template <class AllocationPolicy>
    class Allocator
    {
    public:
        Allocator(void* start, void* end, size_t elementSize)
            : mAllocationPolicy(start, end, elementSize)
        {}

        auto allocate() noexcept -> void*
        {
            return mAllocationPolicy.allocate();
        }

        auto deallocate(void* ptr) noexcept -> void
        {
            mAllocationPolicy.deallocate(ptr);
        }

        auto reset() noexcept -> void
        {
            mAllocationPolicy.reset();
        }

    private:
        AllocationPolicy mAllocationPolicy;

        int mAllocations = 0;
        int mDeallocations = 0;
    };

    TOV_NAMESPACE_END // memory
}
