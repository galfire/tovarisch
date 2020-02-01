#ifndef TOV_RENDERING_PLATFORMS_WEB_WINDOW_PLATFORM_SUPPORT_WEB_H
#define TOV_RENDERING_PLATFORMS_WEB_WINDOW_PLATFORM_SUPPORT_WEB_H

#include <rendering/rendering_core.h>

#include <rendering/window_platform_support.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformComponent;

	TOV_NAMESPACE_BEGIN(platforms)
	TOV_NAMESPACE_BEGIN(web)

	class WindowPlatformSupportWeb
		: WindowPlatformSupport
	{
	public:
		std::unique_ptr<WindowPlatformComponent> buildComponent() const override;
	};

	TOV_NAMESPACE_END // web
	TOV_NAMESPACE_END // platforms
	TOV_NAMESPACE_END // rendering
}

#endif
