#ifndef TOV_MEMORY_ARENA_ALLOCATION_HEADER_H
#define TOV_MEMORY_ARENA_ALLOCATION_HEADER_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(arena)

    struct AllocationHeader
    {
        void* originalPtr;
        size_t allocationSize;
    };

    TOV_NAMESPACE_END
    TOV_NAMESPACE_END
}

#endif
