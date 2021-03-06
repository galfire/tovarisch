#ifndef TOV_RENDERING_WINDOW_PLATFORM_SUPPORT_H
#define TOV_RENDERING_WINDOW_PLATFORM_SUPPORT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;
	class WindowPlatformComponent;

	class WindowPlatformSupport
	{
	public:
		WindowPlatformSupport() = default;
		virtual ~WindowPlatformSupport() = default;

		virtual auto buildComponent(Window& parentWindow) const -> std::unique_ptr<WindowPlatformComponent> TOV_ABSTRACT;

		virtual void messageHandler() TOV_ABSTRACT;
	};

	TOV_NAMESPACE_END
}

#endif