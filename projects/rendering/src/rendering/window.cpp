#include <rendering/window.h>

#include "rendering/window_platform_component.h"
#include "rendering/window_platform_support.h"
#include "rendering/window_renderer_component.h"
#include "rendering/window_renderer_support.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Window::Window(
        const WindowPlatformSupport& platformSupport,
        const WindowRendererSupport& rendererSupport,
        const char* name,
        uint width,
        uint height,
        bool fullscreen,
        bool visible,
        PixelFormat pixelFormat
    )
        : mPlatformSupport(platformSupport)
        , mRendererSupport(rendererSupport)
        , mName(name)
        , mWidth(width)
        , mHeight(height)
        , mFullscreen(fullscreen)
        , mVisible(visible)
        , mPixelFormat(pixelFormat)
    {
        mPlatformComponent = mPlatformSupport.buildComponent(*this);
        mPlatformComponent->create();

        mRendererComponent = mRendererSupport.buildComponent(*this);
        mRendererComponent->create();
    }

    Window::~Window()
    {}

    const WindowPlatformComponent& Window::getPlatformComponent() const
    {
        return *mPlatformComponent.get();
    }

    const WindowRendererComponent& Window::getRendererComponent() const
    {
        return *mRendererComponent;
    }

    TOV_NAMESPACE_END // rendering
}