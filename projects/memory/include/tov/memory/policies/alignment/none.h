#ifndef TOV_MEMORY_POLICIES_ALIGNMENT_NONE_H
#define TOV_MEMORY_POLICIES_ALIGNMENT_NONE_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(alignment)

    class None
    {
    public:
        inline constexpr size_t determineAlignmentSpace(size_t alignment) noexcept
        {
            return 0;
        }

        inline void* align(size_t alignment, size_t size, void*& ptr, size_t& space) noexcept
        {
            return ptr;
        }

        inline void writeHeader(void*& ptr, size_t alignmentSpace, ptrdiff_t alignmentOffset) noexcept {}
        inline void readHeader(void*& ptr, size_t& alignmentSpace, ptrdiff_t& alignmentOffset) noexcept
        {
            alignmentSpace = 0;
            alignmentOffset = 0;
        }

    public:
        constexpr static size_t POLICY_OFFSET = 0;
    };

    TOV_NAMESPACE_END // alignment
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#endif
