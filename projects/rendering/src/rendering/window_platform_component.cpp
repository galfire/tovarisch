#include <rendering/window_platform_component.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	WindowPlatformComponent::WindowPlatformComponent(Window& parentWindow)
		: mParentWindow(parentWindow)
	{}

	void WindowPlatformComponent::create()
	{
		_create();
	}

	void WindowPlatformComponent::destroy()
	{
		_destroy();
	}

	TOV_NAMESPACE_END // rendering
}