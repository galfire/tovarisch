#pragma once

#include <tov/core.h>

#include "allocator.h"
#include "heap_area.h"

#include "policies/allocation/freelist.h"
#include "policies/allocation/stack.h"

#include <type_traits>
#include <vector>
#include <array>
#include <functional>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    using id = unsigned int;

    template <class T>
    struct Handle
    {
        unsigned int index;
    };

    template <class T>
    concept Containerable = std::is_move_assignable_v<T>;

    template <Containerable T, size_t N>
    class Container
    {
    public:
        class Creator;
        class Iterator;

    private:
        using HandleT = Handle<T>;

    public:
        Container()
            : mHeapArea(sizeof(T) * N)
            , mCreator(mHeapArea)
        {}
        ~Container() = default;

        template <class... U>
        auto emplace_back(U&&... args) -> auto
        {
            assert(mCount < N);

            mT.push_back(mCreator.create(std::forward<U>(args)...));

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

        auto delete_at(id i) noexcept
        {
            auto handle = mHandles[i];
            delete_at(handle);
        }

        auto begin() const { return Iterator{ &this->data()[0] }; }
        auto end() const { return Iterator{ &this->data()[mCount] }; }
        auto size() const { return mCount; }

    private:
        auto data() const
        {
            return static_cast<T*>(mHeapArea.getStart());
        }

        auto delete_at(HandleT h) noexcept
        {
            auto index = h.index;
            auto ptr = mT[index].get();

            {
                // Delete the data
                auto _ = std::move(mT[index]);
            }

            // Defragment the heap area
            
            {
                // Move t_last data into location of deleted data
                auto& t_deleted = *static_cast<T*>(ptr);
                auto& t_last = this->data()[mCount - 1];
                t_deleted = std::move(t_last);
            }

            {
                // Repoint t_last ptr to the moved data's new location
                auto& t_last_ptr = mT[mCount - 1];
                t_last_ptr.release();
                t_last_ptr.reset(ptr);
            }

            mCount--;
        }

    private:
        unsigned int mCount = 0u;
        
        HeapArea mHeapArea;
        Creator mCreator;

        std::vector<typename Creator::UT> mT;
        std::vector<HandleT> mHandles;
    };

    template <Containerable T, size_t N>
    class Container<T, N>::Creator
    {
    public:
        using Deleter = std::function<void(T*)>;
        using UT = std::unique_ptr<T, Deleter>;
        using AllocationPolicy = policies::allocation::Stack;

    public:
        Creator(HeapArea const& heapArea)
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

    private:
        Allocator<AllocationPolicy> mAllocator;
    };

    template <Containerable T, size_t N>
    class Container<T, N>::Iterator
    {
    public:
        using value_type = T;
        using element_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::contiguous_iterator_tag;
        using difference_type = ptrdiff_t;

    public:
        Iterator() noexcept = default;
        ~Iterator() noexcept = default;

        Iterator(const Iterator& it) noexcept
            : mPtr(it.mPtr)
        {}

        Iterator(Iterator&& it) noexcept
            : mPtr(it.mPtr)
        {}

        Iterator(pointer ptr) noexcept
            : mPtr(ptr)
        {}

        auto operator=(const Iterator& rhs) -> auto&
        {
            mPtr = rhs.mPtr;
            return *this;
        }

        auto operator-(const Iterator& rhs) const
        {
            return difference_type{ this->mPtr - rhs.mPtr };
        }

        auto operator+(difference_type n) const
        {
            auto tmp = *this;
            tmp.mPtr += n;
            return tmp;
        }

        auto operator+=(difference_type n) -> auto&
        {
            mPtr += n;
            return *this;
        }

        auto operator-(difference_type n) const
        {
            auto tmp = *this;
            tmp.mPtr -= n;
            return tmp;
        }

        auto operator-=(difference_type n) -> auto&
        {
            mPtr -= n;
            return *this;
        }

        auto operator++() -> Iterator&
        {
            mPtr++;
            return *this;
        }

        friend
        auto operator+(difference_type n, const Iterator j)
        {
            auto tmp = Iterator{ j.mPtr + n };
            return tmp;
        }

        auto operator--() -> auto&
        {
            mPtr--;
            return *this;
        }

        auto operator--(int)
        {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        auto operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        auto operator[](difference_type n) const -> reference
        {
            auto tmp = Iterator{ mPtr + n };
            return *tmp;
        }

        auto operator*() -> reference
        { 
            return *mPtr;
        }
        
        auto operator*() const -> std::add_const_t<reference>
        { 
            return *mPtr;
        }

        auto operator->() -> pointer
        {
            return mPtr;
        }
        
        auto operator->() const -> std::add_const_t<pointer>
        {
            return mPtr;
        }

        auto operator==(Iterator const& other) const
        {
            return mPtr == other.mPtr;
        }

        auto operator!=(Iterator const& other) const
        {
            return !(*this == other);
        }

        auto operator<(Iterator const& other) const
        {
            return mPtr < other.mPtr;
        }

        auto operator>(Iterator const& other) const
        {
            return mPtr > other.mPtr;
        }

        auto operator<=(Iterator const& other) const
        {
            return mPtr <= other.mPtr;
        }

        auto operator>=(Iterator const& other) const
        {
            return mPtr >= other.mPtr;
        }

    private:
        pointer mPtr;
    };

    namespace
    {
        using Iterator = Container<int, 4>::Iterator;

        template <class I>
        concept random_access_iterator_test = requires(I i, const I j, const std::iter_difference_t<I> n)
        {
            { i += n } -> std::same_as<I&>;
            { j + n } -> std::same_as<I>;
            { n + j } -> std::same_as<I>;
            { i -= n } -> std::same_as<I&>;
            { i - n } -> std::same_as<I>;
            { j[n] } -> std::same_as<std::iter_reference_t<I>>;
        };

        template <class I>
        concept contiguous_iterator_test = requires(const I & i)
        {
            { std::to_address(i) } -> std::same_as<std::add_pointer_t<std::iter_reference_t<I>>>;
        };

        static_assert(std::is_object_v<Iterator>, "Iterator must be object.");
        static_assert(std::is_nothrow_destructible_v<Iterator>, "Iterator must be nothrow destructible.");
        static_assert(std::destructible<Iterator>, "Iterator must be destructible.");
        static_assert(std::constructible_from<Iterator, Iterator>, "Iterator must be constructible from itself.");
        static_assert(std::move_constructible<Iterator>, "Iterator must be move constructible.");
        static_assert(std::assignable_from<Iterator&, Iterator>, "Iterator must be assignable from.");
        static_assert(std::movable<Iterator>, "Iterator must be movable.");
        static_assert(std::weakly_incrementable<Iterator>, "Iterator must be weakly icrementable.");
        static_assert(std::input_or_output_iterator<Iterator>, "Iterator must be an input or output iterator.");
        static_assert(std::input_iterator<Iterator>, "Iterator must be an input iterator.");
        static_assert(std::forward_iterator<Iterator>, "Iterator must be a forward iterator.");
        static_assert(std::bidirectional_iterator<Iterator>, "Iterator must be a bidirectional iterator.");
        static_assert(std::totally_ordered<Iterator>, "Iterator must be totally ordered.");
        static_assert(std::sized_sentinel_for<Iterator, Iterator>, "Iterator must be a sized sentinel.");
        static_assert(random_access_iterator_test<Iterator>, "Iterator must pass the random access iterator tests.");
        static_assert(std::random_access_iterator<Iterator>, "Iterator must be a random access iterator.");
        static_assert(contiguous_iterator_test<Iterator>, "Iterator must pass the contiguous iterator tests.");
        static_assert(std::contiguous_iterator<Iterator>, "Iterator must be a contiguous iterator.");
    }
    
    TOV_NAMESPACE_END
}
