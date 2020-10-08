#ifndef TOV_RENDERING_PIPELINE_FRAMEBUFFER_ATTACHMENTS_H
#define TOV_RENDERING_PIPELINE_FRAMEBUFFER_ATTACHMENTS_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    enum class FramebufferAttachments
    {
        COLOUR_ATTACHMENT_0 = 1 << 0,
        COLOUR_ATTACHMENT_1 = 1 << 1,
        COLOUR_ATTACHMENT_2 = 1 << 2,
        COLOUR_ATTACHMENT_3 = 1 << 3
    };

    constexpr auto operator & (FramebufferAttachments lhs, FramebufferAttachments rhs)
    {
        return static_cast<FramebufferAttachments>(
            static_cast<std::underlying_type<FramebufferAttachments>::type>(lhs) &
            static_cast<std::underlying_type<FramebufferAttachments>::type>(rhs)
            );
    }

    constexpr auto operator &= (FramebufferAttachments& lhs, FramebufferAttachments rhs) -> auto&
    {
        lhs = static_cast<FramebufferAttachments>(
            static_cast<std::underlying_type<FramebufferAttachments>::type>(lhs) &
            static_cast<std::underlying_type<FramebufferAttachments>::type>(rhs)
            );
        return lhs;
    }

    constexpr auto operator | (FramebufferAttachments lhs, FramebufferAttachments rhs)
    {
        return static_cast<FramebufferAttachments>(
            static_cast<std::underlying_type<FramebufferAttachments>::type>(lhs) |
            static_cast<std::underlying_type<FramebufferAttachments>::type>(rhs)
            );
    }

    constexpr auto operator |= (FramebufferAttachments& lhs, FramebufferAttachments rhs) -> auto&
    {
        lhs = static_cast<FramebufferAttachments>(
            static_cast<std::underlying_type<FramebufferAttachments>::type>(lhs) |
            static_cast<std::underlying_type<FramebufferAttachments>::type>(rhs)
            );
        return lhs;
    }

    constexpr auto operator == (FramebufferAttachments lhs, std::underlying_type<FramebufferAttachments>::type rhs)
    {
        return static_cast<std::underlying_type<FramebufferAttachments>::type>(lhs) == rhs;
    }

    constexpr auto operator != (FramebufferAttachments lhs, std::underlying_type<FramebufferAttachments>::type rhs)
    {
        return !(lhs == rhs);
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif // TOV_RENDERING_PIPELINE_FRAMEBUFFER_H
