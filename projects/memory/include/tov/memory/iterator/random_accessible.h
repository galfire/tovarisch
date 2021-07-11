#pragma once

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(iterator)

    template <class Iterator, class Traits>
    class RandomAccessible
    {
    private:
        using difference_type = Traits::difference_type;

    public:
        auto operator+(difference_type n) const -> Iterator
        {
            auto tmp = static_cast<Iterator const&>(*this);
            &tmp += n;
            return tmp;
        }

        auto operator+=(difference_type n) -> auto&
        {
            auto& self = static_cast<Iterator&>(*this);
            &self += n;
            return self;
        }

        auto operator-(difference_type n) const -> Iterator
        {
            auto tmp = static_cast<Iterator const&>(*this);
            &tmp -= n;
            return tmp;
        }

        auto operator-=(difference_type n) -> auto&
        {
            auto& self = static_cast<Iterator&>(*this);
            &self -= n;
            return self;
        }

        auto operator-(const Iterator& rhs) const
        {
            auto& self = static_cast<Iterator const&>(*this);
            return difference_type{ &self - &rhs };
        }

        friend
        auto operator+(difference_type n, const Iterator j)
        {
            auto tmp = Iterator{ &j + n };
            return tmp;
        }
    };

    TOV_NAMESPACE_END
    TOV_NAMESPACE_END
}
