#ifndef TOV_MEMORY_POLICIES_ALLOCATION_LINEAR_H
#define TOV_MEMORY_POLICIES_ALLOCATION_LINEAR_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(allocation)

    class Linear
    {
    public:
        inline explicit Linear(const void* start, const void* end) noexcept;
        inline ~Linear() noexcept = default;

        inline void* allocate(size_t size);
        inline void deallocate(void* ptr) noexcept;
        inline void reset() noexcept;

    private:
        const void* mStart = nullptr;
        const void* mEnd = nullptr;
        void* mCurrent = nullptr;
    };

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#include "linear.inl"

#endif
