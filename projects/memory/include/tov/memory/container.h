#pragma once

#include <tov/core.h>

#include <tov/memory_config.h>
#include "allocated_object.h"
#include "allocator.h"
#include "heap_area.h"

#include "policies/allocation/freelist.h"
#include "policies/allocation/stack.h"

#include <type_traits>
#include <vector>
#include <span>
#include <array>
#include <functional>
#include <stack>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    using id = unsigned int;

    template <class T> 
    struct Handle
    {
        unsigned int index;
    };

    template <typename T>
    concept Containerable = std::is_move_assignable_v<T>;


    template <Containerable T, size_t N>
    class Container
    {
    private:
        using Deleter = std::function<void(T*)>;
        using UT = std::unique_ptr<T, Deleter>;
        using HandleT = Handle<T>;

        class Creator
        {
        private:
            using AllocationPolicy = policies::allocation::Stack;
            Allocator<AllocationPolicy> mAllocator;

        public:
            Creator(HeapArea& heapArea)
                : mAllocator(heapArea.getStart(), heapArea.getEnd(), sizeof(T))
            {}

            template <class... U>
            auto create(U&&... args) -> auto
            {
                auto location = mAllocator.allocate();
                auto deleter = [](T* t, auto& allocator)
                {
                    t->~T();
                    allocator.deallocate(t);
                };
                auto ut = UT{
                    new (location) T(std::forward<U>(args)...),
                    std::bind(deleter, std::placeholders::_1, std::ref(mAllocator))
                };
                return ut;
            }
        };


    public:
        Container()
            : mHeapArea(sizeof(T) * N)
            , mAllocator(mHeapArea.getStart(), mHeapArea.getEnd(), sizeof(T))
        {
        }

        ~Container() = default;

        template <class... U>
        auto emplace_back(U&&... args) -> auto
        {
            assert(mCount < N);

            {
                auto location = mAllocator.allocate();
                auto deleter = [](T* t, auto& allocator)
                {
                    t->~T();
                    allocator.deallocate(t);
                };
                auto ut = UT{
                    new (location) T(std::forward<U>(args)...),
                    std::bind(deleter, std::placeholders::_1, std::ref(mAllocator))
                };
                mT.push_back(std::move(ut));
            }

            auto h = HandleT{ mHandles.size() };
            mHandles.push_back(h);

            auto i = id{ mHandles.size() - 1 };

            mCount++;

            return i;
        }

        auto operator [] (id i) -> auto&
        {
            auto index = mHandles[i].index;
            auto& t = *mT[index].get();
            return t;
        }

        auto delete_at(id i)
        {
            auto handle = mHandles[i];
            delete_at(handle);
        }

        auto delete_at(HandleT h)
        {
            auto index = h.index;
            auto ptr = mT[index].get();

            {
                // Delete the data
                auto _ = std::move(mT[index]);
            }

            {
                // Defragment the heap area
                
                // Move t_last data into location of deleted data
                auto& t_delete = *static_cast<T*>(ptr);
                T* data = static_cast<T*>(mHeapArea.getStart());
                auto& t_last = data[mCount - 1];
                t_delete = std::move(t_last);

                // Repoint t_last ptr to the moved data's new location
                mT[mCount - 1].release();
                mT[mCount - 1].reset(&t_delete);
            }

            mCount--;
        }

        auto data()
        {
            return static_cast<T*>(mHeapArea.getStart());
        }
        
    private:
        unsigned int mCount = 0u;
        
        HeapArea mHeapArea;
        using AllocationPolicy = policies::allocation::Stack;
        Allocator<AllocationPolicy> mAllocator;

        std::vector<UT> mT;

        std::vector<HandleT> mHandles;
    };

    TOV_NAMESPACE_END
}
