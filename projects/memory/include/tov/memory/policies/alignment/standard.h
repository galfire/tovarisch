#ifndef TOV_MEMORY_POLICIES_ALIGNMENT_STANDARD_H
#define TOV_MEMORY_POLICIES_ALIGNMENT_STANDARD_H

#include <tov/core.h>

#include "../../memory_accessor.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(alignment)

    class Standard
    {
    private:
        struct BlockHeader
        {
            size_t alignmentSpace;
            ptrdiff_t alignmentOffset;
        };

    public:
        inline explicit Standard() noexcept = default;
        inline ~Standard() noexcept = default;

        inline size_t determineAlignmentSpace(size_t alignment) noexcept;
        inline void* align(size_t alignment, size_t size, void*& ptr, size_t& space) noexcept;

        inline void writeHeader(void*& ptr, size_t alignmentSpace, ptrdiff_t alignmentOffset) const noexcept;
        inline void readHeader(void*& ptr, size_t& alignmentSpace, ptrdiff_t& alignmentOffset) const noexcept;

    private:
        MemoryAccessor<BlockHeader> accessor;

    public:
        constexpr static size_t POLICY_OFFSET = sizeof(BlockHeader);
    };

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#include "standard.inl"

#endif
