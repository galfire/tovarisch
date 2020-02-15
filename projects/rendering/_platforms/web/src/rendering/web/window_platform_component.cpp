#include "rendering/web/window_platform_component.h"

#include <tov/rendering/window.h>

#include "rendering/web/device_context.h"

#include <emscripten/html5.h>

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
		const char* canvasID = mParentWindow.getName();
		mDeviceContext = std::make_unique<DeviceContext>(canvasID);

		const uint width = mParentWindow.getWidth();
		const uint height = mParentWindow.getHeight();

		emscripten_set_canvas_element_size(canvasID, width, height);
	}

	void WindowPlatformComponent::_destroy()
	{

	}

	TOV_NAMESPACE_END // web
	TOV_NAMESPACE_END // rendering
}