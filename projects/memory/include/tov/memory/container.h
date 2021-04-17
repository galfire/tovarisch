#pragma once

#include <tov/core.h>

#include <tov/memory_config.h>
#include "allocated_object.h"

#include <vector>
#include <span>
#include <array>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template <class T, size_t N>
    class Container
    {
    private:
        using Arena = ArenaFreelist<T>;
        static constexpr size_t ALLOCATED_T_MEMORY = N * Arena::ALLOCATION_SPACE;
        class AllocatedT
            : public T
            , public AllocatedObject<Arena, ALLOCATED_T_MEMORY>
        {};

    public:
        Container() = default;
        ~Container() = default;

        template <class... U>
        auto emplace_back(U&&... args) -> auto&
        {
            assert(mCount < N);

            {
                auto t = std::make_unique<AllocatedT>(std::forward<U>(args)...);
                mT.push_back(std::move(t));
            }

            auto t = mT.back().get();
            mT_.push_back(t);

            mCount++;

            return *t;
        }

        auto operator [] (unsigned int i)
        {
            //return mT_[i];
        }

        constexpr auto size()
        {
            return mCount;
        }

        constexpr auto data()
        {
            //return mT_;
        }

    private:
        unsigned int mCount = 0u;
        std::vector<std::unique_ptr<AllocatedT>> mT;
        std::vector<T*> mT_;
    };


    TOV_NAMESPACE_END
}
