#pragma once

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(iterator)

    template <class Iterator, class Traits>
    class Subscriptable
    {
    private:
        using difference_type = Traits::difference_type;
        using reference = Traits::reference;

    public:
        auto operator[](difference_type n) const -> reference
        {
            auto& self = static_cast<Iterator&>(*this);
            auto tmp = Iterator{ &self + n };
            return *tmp;
        }
    };

    TOV_NAMESPACE_END
    TOV_NAMESPACE_END
}
