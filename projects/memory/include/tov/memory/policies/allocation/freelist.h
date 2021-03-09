#ifndef TOV_MEMORY_POLICIES_ALLOCATION_FREELIST_H
#define TOV_MEMORY_POLICIES_ALLOCATION_FREELIST_H

#include <tov/core.h>
#include <tov/gear/freelist.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(allocation)

    class Freelist
    {
    public:
        inline explicit Freelist(void* start, void* end, size_t elementSize) noexcept;
        inline ~Freelist() noexcept = default;

        inline auto allocate() noexcept -> void*;
        inline auto deallocate(void* ptr) noexcept -> void;
        inline auto reset() noexcept -> void;

    private:
        gear::Freelist mFreelist;
        void* mStart;
        void* mEnd;
        size_t mElementSize;
    };

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#include "freelist.inl"

#endif
