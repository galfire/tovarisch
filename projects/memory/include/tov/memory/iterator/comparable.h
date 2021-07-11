#pragma once

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(iterator)

    template <class Iterator>
    class Comparable
    {
    public:
        auto operator==(Iterator const& other) const -> bool
        {
            auto& self = static_cast<Iterator const>(*this);
            return &self == &other;
        }

        auto operator!=(Iterator const& other) const -> bool
        {
            auto& self = static_cast<Iterator const>(*this);
            return &self != &other;
        }
    };

    TOV_NAMESPACE_END
    TOV_NAMESPACE_END
}
