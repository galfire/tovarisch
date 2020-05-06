#include <cstring> // std::memcpy
#include <new>

#include <iostream>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(allocation)

    inline Linear::Linear(const void* start, const void* end) noexcept
    {
        mStart = start;
        mEnd = end;
        mCurrent = (void*)mStart;
    }

    inline void* Linear::allocate(size_t size)
    {
        if((uintptr_t)mCurrent + sizeof(BlockHeader) + size >= (uintptr_t)mEnd)
        {
            throw std::bad_alloc();
        }

        union
        {
            void* asRaw;
            byte* asByte;
        };
        asRaw = mCurrent;

        BlockHeader header;
        header.mAllocationSize = size;
        // Append the header
        memcpy(asRaw, &header, sizeof(BlockHeader));

        // Return the memory after the header
        asByte += sizeof(BlockHeader);
        void* userPtr = asByte;

        asByte += size;
        mCurrent = asRaw;

        return userPtr;
    }

    inline void Linear::deallocate(void* ptr) noexcept
    {
        (void)ptr;
    }

    inline void Linear::reset() noexcept
    {
        mCurrent = (void*)mStart;
    }

    inline size_t Linear::getAllocationSize(void* ptr) const noexcept
    {
        union
        {
            void* asRaw;
            BlockHeader* asHeader;
        };

        asRaw = ptr;
        size_t userDataSize = asHeader[-1].mAllocationSize;
        return userDataSize;
    }

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}
