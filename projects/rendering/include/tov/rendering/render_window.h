#ifndef TOV_RENDERING_RENDER_WINDOW_H
#define TOV_RENDERING_RENDER_WINDOW_H

#include "rendering_core.h"

#include "render_target.h"
#include "window.h"

#include "pixel_format.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;

    class RenderWindow
        : public RenderTarget
        , public Window
    {
    public:
        RenderWindow(
            RenderSystem& renderSystem,
            const WindowPlatformSupport& platformSupport,
            const WindowRendererSupport& rendererSupport,
            const char* name,
            uint width,
            uint height,
            bool fullscreen,
            bool visible = true,
            PixelFormat pixelFormat = PixelFormat::Default
        );
        ~RenderWindow() = default;

        void prerender() override;
        void swapBuffers() override;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
