#include "rendering/platforms/win32/window_platform_support_win32.h"

#include "rendering/platforms/win32/window_platform_component_win32.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(platforms)
	TOV_NAMESPACE_BEGIN(win32)

	std::unique_ptr<WindowPlatformComponent> WindowPlatformSupportWin32::buildComponent(Window& parentWindow) const
	{
		return std::unique_ptr<WindowPlatformComponent>(new WindowPlatformComponentWin32(parentWindow));
	}

	TOV_NAMESPACE_END // win32
	TOV_NAMESPACE_END // platforms
	TOV_NAMESPACE_END // rendering
}