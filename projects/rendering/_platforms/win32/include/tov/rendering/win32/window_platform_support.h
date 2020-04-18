#ifndef TOV_RENDERING_WIN32_WINDOW_PLATFORM_SUPPORT_H
#define TOV_RENDERING_WIN32_WINDOW_PLATFORM_SUPPORT_H

#include <tov/rendering/window_platform_support.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class WindowPlatformComponent;

    TOV_NAMESPACE_BEGIN(win32)

    class WindowPlatformSupport
        : public rendering::WindowPlatformSupport
    {
    public:
        WindowPlatformSupport();
        ~WindowPlatformSupport() = default;

        std::unique_ptr<rendering::WindowPlatformComponent> buildComponent(Window& parentWindow) const override;

        void messageHandler() override;

    private:
        void registerWndClasses() const;
    };

    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}

#endif
