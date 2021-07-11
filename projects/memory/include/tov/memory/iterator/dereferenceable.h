#pragma once

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(iterator)

    template <class Iterator, class Traits>
    class Dereferenceable
    {
    private:
        using reference = Traits::reference;

    public:
        auto operator*() -> reference
        {
            auto self = static_cast<Iterator*>(this);
            return *self->ptr();
        }

        auto operator*() const -> std::add_const_t<reference>
        {
            auto self = static_cast<Iterator const*>(this);
            return *self->ptr();
        }
    };

    TOV_NAMESPACE_END
    TOV_NAMESPACE_END
}
