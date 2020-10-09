#include "rendering_gl/render_system.h"

#include "rendering_gl/texture/texture.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)

    RenderSystem::RenderSystem(
        WindowPlatformSupport& windowPlatformSupport,
        WindowRendererSupport& windowRendererSupport
    ) noexcept
        : rendering::RenderSystem(windowPlatformSupport, windowRendererSupport)
    {
    }

    auto RenderSystem::createTexture2D(
        rendering::buffers::PixelBufferObject& pbo,
        uint width,
        uint height,
        PixelFormat pixelFormat
    ) -> rendering::texture::Texture2D&
    {
        auto texture = mRenderTargetManager.template create<rendering::gl::texture::Texture2D>(
            pbo,
            width,
            height,
            pixelFormat
        );
        return *texture;
    }

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}
