#ifndef TOV_RENDERING_BUFFERS_ACCESS_SETTINGS
#define TOV_RENDERING_BUFFERS_ACCESS_SETTINGS

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    enum class AccessSettings : unsigned int
    {
        // Can the buffer be read on lock?
        READ	 = 1 << 0,
        NO_READ  = 0 << 0,
        // Can the buffer be written on unlock?
        WRITE	 = 1 << 1,
        NO_WRITE = 0 << 1,
    };

    constexpr auto operator & (AccessSettings lhs, AccessSettings rhs)
    {
        return static_cast<AccessSettings>(
            static_cast<std::underlying_type<AccessSettings>::type>(lhs) &
            static_cast<std::underlying_type<AccessSettings>::type>(rhs)
        );
    }

    constexpr auto operator &= (AccessSettings& lhs, AccessSettings rhs) -> auto&
    {
        lhs = static_cast<AccessSettings>(
            static_cast<std::underlying_type<AccessSettings>::type>(lhs) &
            static_cast<std::underlying_type<AccessSettings>::type>(rhs)
        );
        return lhs;
    }

    constexpr auto operator | (AccessSettings lhs, AccessSettings rhs)
    {
        return static_cast<AccessSettings>(
            static_cast<std::underlying_type<AccessSettings>::type>(lhs) |
            static_cast<std::underlying_type<AccessSettings>::type>(rhs)
        );
    }

    constexpr auto operator |= (AccessSettings& lhs, AccessSettings rhs) -> auto&
    {
        lhs = static_cast<AccessSettings>(
            static_cast<std::underlying_type<AccessSettings>::type>(lhs) |
            static_cast<std::underlying_type<AccessSettings>::type>(rhs)
        );
        return lhs;
    }

    constexpr auto operator == (AccessSettings lhs, std::underlying_type<AccessSettings>::type rhs)
    {
        return static_cast<std::underlying_type<AccessSettings>::type>(lhs) == rhs;
    }

    constexpr auto operator != (AccessSettings lhs, std::underlying_type<AccessSettings>::type rhs)
    {
        return !(lhs == rhs);
    }

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_BUFFERS_ACCESS_SETTINGS
