#include "rendering/web/window_platform_support.h"

#include "rendering/web/window_platform_component.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(web)

    WindowPlatformSupport::WindowPlatformSupport() noexcept
        : rendering::WindowPlatformSupport()
    {}

    std::unique_ptr<rendering::WindowPlatformComponent> WindowPlatformSupport::buildComponent(Window& parentWindow) const
    {
        return std::make_unique<WindowPlatformComponent>(parentWindow);
    }

    void WindowPlatformSupport::messageHandler()
    {}

    TOV_NAMESPACE_END // web
    TOV_NAMESPACE_END // rendering
}
