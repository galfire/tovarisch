#ifndef TOV_MEMORY_POLICIES_ALIGNMENT_STANDARD_H
#define TOV_MEMORY_POLICIES_ALIGNMENT_STANDARD_H

#include <tov/core.h>
#include <cassert>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(alignment)

    class Standard
    {
    public:
        inline explicit constexpr Standard() noexcept = default;
        inline ~Standard() noexcept = default;

        inline constexpr auto determineAlignmentSpace(size_t alignment) noexcept
        {
            return alignment - 1;
        }
        inline auto align(size_t alignment, size_t size, void*& ptr, size_t& space) noexcept
        {
            // Can we shift the requested memory block forward to an aligned address within the allocated space?
            assert(std::align(alignment, size, ptr, space));
            // The test pointer can successfully be aligned; align the user pointer now
            void* alignedPtr = std::align(alignment, size, ptr, space);
            assert((uintptr_t)ptr % alignment == 0);
            return alignedPtr;
        }
    };

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#endif
