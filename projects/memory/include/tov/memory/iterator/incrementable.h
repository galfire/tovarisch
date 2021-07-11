#pragma once

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(iterator)

    template <class Iterator>
    class Incrementable
    {
    public:
        auto operator++() -> auto&
        {
            auto self = static_cast<Iterator*>(this);
            self->ptr()++;
            return *self;
        }

        auto operator--() -> auto&
        {
            auto self = static_cast<Iterator*>(this);
            self->ptr()--;
            return *self;
        }

        auto operator--(int)
        {
            auto tmp = static_cast<Iterator*>(this);
            --(*this);
            return *tmp;
        }

        auto operator++(int)
        {
            auto tmp = static_cast<Iterator*>(this);
            ++(*this);
            return *tmp;
        }
    };

    TOV_NAMESPACE_END
    TOV_NAMESPACE_END
}
