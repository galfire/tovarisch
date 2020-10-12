#ifndef TOV_RENDERING_GL_RENDER_SYSTEM_H
#define TOV_RENDERING_GL_RENDER_SYSTEM_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/render_system.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    class WindowPlatformSupport;
    class WindowRendererSupport;
    TOV_NAMESPACE_END

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)

    class RenderSystem
        : public rendering::RenderSystem
    {
    public:
        using rendering::RenderSystem::RenderSystem;

        virtual auto createTexture2D(
            uint width,
            uint height,
            PixelFormat pixelFormat
        ) -> rendering::texture::Texture2D& override;
    };

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
