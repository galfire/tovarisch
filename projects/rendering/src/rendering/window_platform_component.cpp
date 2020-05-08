#include <rendering/window_platform_component.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    WindowPlatformComponent::WindowPlatformComponent(Window& parentWindow)
        : mParentWindow(parentWindow)
    {}

    void WindowPlatformComponent::create()
    {
        createImpl();
    }

    void WindowPlatformComponent::destroy()
    {
        destroyImpl();
    }

    TOV_NAMESPACE_END // rendering
}
