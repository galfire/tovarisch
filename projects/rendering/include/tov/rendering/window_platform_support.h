#ifndef TOV_RENDERING_WINDOW_PLATFORM_SUPPORT_H
#define TOV_RENDERING_WINDOW_PLATFORM_SUPPORT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformComponent;

	class WindowPlatformSupport
	{
	public:
		WindowPlatformSupport() = default;
		virtual ~WindowPlatformSupport() = default;

		virtual std::unique_ptr<WindowPlatformComponent> buildComponent() const;
	};

	TOV_NAMESPACE_END
}

#endif