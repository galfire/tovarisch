#ifndef TOV_MEMORY_ALLOCATED_OBJECT_H
#define TOV_MEMORY_ALLOCATED_OBJECT_H

#include <tov/core.h>
#include "memory.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template<typename Arena, typename Area, size_t Sz>
    class AllocatedObject
    {
    public:
        explicit AllocatedObject() = default;
        virtual ~AllocatedObject() = default;

        static void* operator new(size_t sz)
        {
            return sArena->allocate();
        };

        static void operator delete(void* ptr)
        {
            sArena->deallocate(ptr);
        }

        static void* operator new[](size_t sz)
        {
            return sArena->allocate(sz);
        }

        static void operator delete[](void* ptr)
        {
            sArena->deallocate(ptr);
        }

        inline static void reset()
        {
            sArena->reset();
        }

    private:
        static Area* sArea = new Area();
        static Arena* sArena = new Arena(
            sArea->getStart(),
            sArea->getEnd()
        );
    };

    TOV_NAMESPACE_END // memory
}

#endif
