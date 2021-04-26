#pragma once

#include <tov/core.h>

#include <tov/memory_config.h>
#include "allocated_object.h"
#include "allocator.h"
#include "heap_area.h"

#include "policies/allocation/freelist.h"

#include <vector>
#include <span>
#include <array>
#include <functional>
#include <stack>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template <class T> 
    struct Handle
    {
        T* ptr;
    };

    template <class T, size_t N>
    class Container
    {
    private:
        using Deleter = std::function<void(T*)>;
        using UT = std::unique_ptr<T, Deleter>;


        using HandleT = Handle<T>;
        using UHandle = std::unique_ptr<HandleT, Deleter>;

    public:
        Container()
            : mHeapArea(sizeof(T) * N)
            , mAllocator(mHeapArea.getStart(), mHeapArea.getEnd(), sizeof(T))
        {}
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

            mCount++;

            return nullptr;
        }

        auto operator [] (unsigned int i) -> auto&
        {
            return *mT[i].get();
        }

        auto delete_at(unsigned int i)
        {
            {
                auto p = std::move(mT[i]);
            }

            mCount--;
        }
        
        auto size() const
        {
            return mCount;
        }

        auto data() const
        {
            //return mT_;
        }

    private:
        unsigned int mCount = 0u;
        
        HeapArea mHeapArea;
        Allocator<policies::allocation::Freelist> mAllocator;



        std::vector<UT> mT;
        

        std::vector<HandleT> mHandles;

    };

    TOV_NAMESPACE_END
}
