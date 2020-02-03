#include <rendering/window_platform_component.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	WindowPlatformComponent::WindowPlatformComponent(Window& parentWindow)
		: mParentWindow(parentWindow)
	{
	}

	WindowPlatformComponent::~WindowPlatformComponent()
	{
	}

	TOV_NAMESPACE_END // rendering
}