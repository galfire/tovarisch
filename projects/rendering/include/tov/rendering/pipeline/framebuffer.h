#ifndef TOV_RENDERING_PIPELINE_FRAMEBUFFER_H
#define TOV_RENDERING_PIPELINE_FRAMEBUFFER_H

#include <tov/rendering/rendering_core.h>

#include "framebuffer_attachments.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    TOV_NAMESPACE_BEGIN(texture)
    class Texture2D;
    TOV_NAMESPACE_END // texture

    TOV_NAMESPACE_BEGIN(pipeline)

    class Framebuffer
    {
    public:
        Framebuffer(bool isDefault = false)
            : mIsDefault(isDefault)
        {}
        virtual ~Framebuffer() = default;

        auto attachTexture(texture::Texture2D const * const texture, FramebufferAttachments attachment) -> void;
        auto bind() const -> void { bindImpl(); }

    private:
        virtual auto attachTextureImpl(texture::Texture2D const* const texture, FramebufferAttachments attachment) -> void TOV_ABSTRACT;
        virtual auto bindImpl() const -> void TOV_ABSTRACT;

    protected:
        bool mIsDefault = false;
        uint mNumAttachments = 0;
        FramebufferAttachments mFrameBufferAttachments;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif // TOV_RENDERING_PIPELINE_FRAMEBUFFER_H
