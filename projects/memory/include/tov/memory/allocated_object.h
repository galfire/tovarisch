#ifndef TOV_MEMORY_ALLOCATED_OBJECT_H
#define TOV_MEMORY_ALLOCATED_OBJECT_H

#include <tov/core.h>
#include "memory.h"
#include "heap_area.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template<
        class Arena,
        size_t Sz
    >
    class AllocatedObject
    {
    public:
        static void* operator new(size_t sz)
        {
            return sArena->allocate();
        };

        static void operator delete(void* ptr)
        {
            sArena->deallocate(ptr);
        }

        static void reset()
        {
            sArena->reset();
        }

    private:
        static inline HeapArea* sArea = new HeapArea(Sz);
        static inline Arena* sArena = new Arena(
            sArea->getStart(),
            sArea->getEnd()
        );
    };

    TOV_NAMESPACE_END // memory
}

#endif
