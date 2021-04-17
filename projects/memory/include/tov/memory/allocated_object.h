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
        static auto operator new(size_t sz) -> void*
        {
            return sArena->allocate();
        };

        static auto operator delete(void* ptr) -> void
        {
            sArena->deallocate(ptr);
        }

        static auto operator new[](size_t sz) -> void* = delete;
        static auto operator delete[](void* ptr) -> void = delete;

        static auto reset()
        {
            sArena->reset();
        }

        static auto getMemoryStart()
        {
            return sArea->getStart();
        }

        static auto getMemorySize()
        {
            return sArea->getSize();
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
