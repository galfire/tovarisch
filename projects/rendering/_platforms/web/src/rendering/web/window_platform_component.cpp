#include "rendering/web/window_platform_component.h"

#include "rendering/web/device_context.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(web)

	WindowPlatformComponent::WindowPlatformComponent(Window& window)
		: rendering::WindowPlatformComponent(window)
	{

	}

	void WindowPlatformComponent::swapBuffers()
	{
	}

	void WindowPlatformComponent::_create()
	{
		const char* canvasID = nullptr;
		mDeviceContext = std::make_unique<DeviceContext>(nullptr);

	}

	void WindowPlatformComponent::_destroy()
	{

	}

	TOV_NAMESPACE_END // web
	TOV_NAMESPACE_END // rendering
}