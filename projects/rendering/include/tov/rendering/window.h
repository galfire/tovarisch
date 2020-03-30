#ifndef TOV_RENDERING_WINDOW_H
#define TOV_RENDERING_WINDOW_H

#include "rendering_core.h"

#include "pixel_format.h"
#include "window_platform_component.h"
#include "window_renderer_component.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class WindowPlatformSupport;
    class WindowRendererSupport;

    class Window
    {
    public:
        Window(
            const WindowPlatformSupport& platformSupport,
            const WindowRendererSupport& rendererSupport,
            const char* name,
            uint width,
            uint height,
            bool fullscreen,
            bool visible = true,
            PixelFormat pixelFormat = PixelFormat::Default
        );
        virtual ~Window() = default;

        const char* getName() const { return mName; }
        uint getWidth() const { return mWidth; }
        uint getHeight() const { return mHeight; }
        bool getFullscreen() const { return mFullscreen; }
        bool getVisible() const { return mVisible; }
        PixelFormat getPixelFormat() const { return mPixelFormat; }

        const WindowPlatformComponent& getPlatformComponent() const;
        const WindowRendererComponent& getRendererComponent() const;

    protected:
        const WindowPlatformSupport& mPlatformSupport;
        const WindowRendererSupport& mRendererSupport;
        const char* mName;
        uint mWidth;
        uint mHeight;
        bool mFullscreen;
        bool mVisible;
        PixelFormat mPixelFormat;

        std::unique_ptr<WindowPlatformComponent> mPlatformComponent;
        std::unique_ptr<WindowRendererComponent> mRendererComponent;
    };

    TOV_NAMESPACE_END // rendering
}

#endif