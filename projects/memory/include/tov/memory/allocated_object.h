#ifndef TOV_MEMORY_ALLOCATED_OBJECT_H
#define TOV_MEMORY_ALLOCATED_OBJECT_H

#include <tov/core.h>
#include "memory.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template<class T, class... Args>
    inline auto ptr(Args&&... args)
    {
        return new (alignof(T)) T(std::forward<Args>(args)...);
    }

    template<class T, size_t N>
    inline auto ptr_array()
    {
        return new (alignof(T)) T[N];
    }

    template<typename Arena, typename Area, size_t Sz>
    class AllocatedObject
    {
    public:
        explicit AllocatedObject() = default;
        virtual ~AllocatedObject() = default;

        static void* operator new(size_t sz, size_t alignment)
        {
            init();
            return sArena->allocate(sz, alignment);
        };

        static void operator delete(void* ptr)
        {
            sArena->deallocate(ptr);
        }

        static void* operator new[](size_t sz, size_t alignment)
        {
            init();
            return sArena->allocate(sz, alignment);
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
        static Area* sArea;
        static Arena* sArena;

        static void init()
        {
            if(sArea == nullptr)
            {
                sArea = new Area(Sz);
                sArena = new Arena(sArea->getStart(), sArea->getEnd());
            }
        }
    };

    template<typename Arena, typename Area, size_t Sz>
    Area* AllocatedObject<Arena, Area, Sz>::sArea = nullptr;

    template<typename Arena, typename Area, size_t Sz>
    Arena* AllocatedObject<Arena, Area, Sz>::sArena = nullptr;

    TOV_NAMESPACE_END // memory
}

#endif
