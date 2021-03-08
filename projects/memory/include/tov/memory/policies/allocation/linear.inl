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
        if((uintptr_t)mCurrent + size >= (uintptr_t)mEnd)
        {
            throw std::bad_alloc();
        }

        void* userPtr = mCurrent;
        mCurrent = static_cast<byte*>(mCurrent) + size;

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

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}
