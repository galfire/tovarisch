#ifndef TOV_RENDERING_GL_PIPELINE_FRAMEBUFFER_H
#define TOV_RENDERING_GL_PIPELINE_FRAMEBUFFER_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/pipeline/framebuffer.h>

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    class FramebufferBinder
    {
    public:
        FramebufferBinder(GLuint textureID)
            : mID(textureID)
            , mTarget(GL_FRAMEBUFFER)
        {
            auto op = log_gl_op("bind framebuffer", mTarget, mID);
            glBindFramebuffer(mTarget, mID);
        }

        ~FramebufferBinder()
        {
            auto op = log_gl_op("unbind framebuffer", mTarget, mID);
            glBindFramebuffer(mTarget, 0);
        }

    private:
        GLuint mID;
        GLenum mTarget;
    };

    class Framebuffer
        : public rendering::pipeline::Framebuffer
    {
    public:
        Framebuffer(bool isDefault = false);
        ~Framebuffer();

    private:
        auto attachTextureImpl(rendering::texture::Texture2D const* const texture, rendering::pipeline::FramebufferAttachments attachment) -> void override;
        auto bindImpl() -> void override;

    private:
        GLuint mFramebufferID;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif // TOV_RENDERING_GL_PIPELINE_FRAMEBUFFER_H
