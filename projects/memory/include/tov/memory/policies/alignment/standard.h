#ifndef TOV_MEMORY_POLICIES_ALIGNMENT_STANDARD_H
#define TOV_MEMORY_POLICIES_ALIGNMENT_STANDARD_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(alignment)

    class Standard
    {
    public:
        inline explicit Standard() noexcept = default;
        inline ~Standard() noexcept = default;

        inline size_t determineAlignmentSpace(size_t alignment) noexcept;
        inline void* align(size_t alignment, size_t size, void*& ptr, size_t& space) noexcept;
    };

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#include "standard.inl"

#endif
