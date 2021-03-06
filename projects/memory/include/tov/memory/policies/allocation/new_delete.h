#ifndef TOV_MEMORY_POLICIES_ALLOCATION_NEW_DELETE_H
#define TOV_MEMORY_POLICIES_ALLOCATION_NEW_DELETE_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(allocation)

    class NewDelete
    {
    public:
        inline explicit NewDelete() noexcept = default;
        inline ~NewDelete() noexcept = default;

        inline void* allocate(size_t size) noexcept;
        inline void deallocate(void* ptr) noexcept;
        inline void reset() noexcept;
    };

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#include "new_delete.inl"

#endif // !TOV_MEMORY_POLICIES_ALLOCATION_NEW_DELETE_H
