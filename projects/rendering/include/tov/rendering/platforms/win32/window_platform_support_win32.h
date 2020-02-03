#ifndef TOV_RENDERING_PLATFORMS_WEB_WINDOW_PLATFORM_SUPPORT_WEB_H
#define TOV_RENDERING_PLATFORMS_WEB_WINDOW_PLATFORM_SUPPORT_WEB_H

#include "../../window_platform_support.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformComponent;

	TOV_NAMESPACE_BEGIN(platforms)
	TOV_NAMESPACE_BEGIN(win32)

	class WindowPlatformSupportWin32
		: public WindowPlatformSupport
	{
	public:
		std::unique_ptr<WindowPlatformComponent> buildComponent(Window& parentWindow) const override;
	};

	TOV_NAMESPACE_END // win32
	TOV_NAMESPACE_END // platforms
	TOV_NAMESPACE_END // rendering
}

#endif
