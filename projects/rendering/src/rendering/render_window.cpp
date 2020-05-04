#include "rendering/render_window.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    RenderWindow::RenderWindow(
        RenderSystem& renderSystem,
        const WindowPlatformSupport& platformSupport,
        const WindowRendererSupport& rendererSupport,
        const char* name,
        uint width,
        uint height,
        bool fullscreen,
        bool visible,
        PixelFormat pixelFormat
    )
        : RenderTarget(
            renderSystem,
            width,
            height,
            pixelFormat
        )
        , Window(
            platformSupport,
            rendererSupport,
            name,
            width,
            height,
            fullscreen,
            visible,
            pixelFormat
        )
    {}

    void RenderWindow::prerender()
    {
        bool success = mRendererComponent->makeContextCurrent();
        assert(success, "Failed to make context current!");
    }

    void RenderWindow::swapBuffers()
    {
        mPlatformComponent->swapBuffers();
    }

    TOV_NAMESPACE_END // rendering
}
