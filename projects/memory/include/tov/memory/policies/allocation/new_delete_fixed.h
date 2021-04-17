#ifndef TOV_MEMORY_POLICIES_ALLOCATION_NEW_DELETE_FIXED_H
#define TOV_MEMORY_POLICIES_ALLOCATION_NEW_DELETE_FIXED_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(allocation)

    class NewDeleteFixed
    {
    public:
        inline explicit NewDeleteFixed(void*, void*, size_t elementSize) noexcept
            : mElementSize(elementSize)
        {}
        inline ~NewDeleteFixed() noexcept = default;

        inline auto allocate() noexcept -> void*
        {
            return ::operator new(mElementSize, std::nothrow);
        }

        inline auto deallocate(void* ptr) noexcept
        {
            ::operator delete(ptr);
        }

        inline auto reset() noexcept
        {}

    private:
        size_t mElementSize;
    };

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#endif // !TOV_MEMORY_POLICIES_ALLOCATION_NEW_DELETE_H
