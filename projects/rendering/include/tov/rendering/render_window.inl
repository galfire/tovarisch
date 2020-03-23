#include "render_window.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    template<class ViewportT>
    RenderWindow<ViewportT>::RenderWindow(
        RenderSystem<ViewportT>& renderSystem,
        const WindowPlatformSupport& platformSupport,
        const WindowRendererSupport& rendererSupport,
        const char* name,
        uint width,
        uint height,
        bool fullscreen,
        bool visible,
        PixelFormat pixelFormat
    )
        : RenderTarget<ViewportT>(
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

    template<class ViewportT>
    void RenderWindow<ViewportT>::prerender()
    {
        mRendererComponent->makeContextCurrent();
    }

    template<class ViewportT>
    void RenderWindow<ViewportT>::swapBuffers()
    {
        mPlatformComponent->swapBuffers();
    }

    TOV_NAMESPACE_END // rendering
}
