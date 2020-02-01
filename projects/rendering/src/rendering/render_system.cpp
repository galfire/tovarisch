#include "rendering/render_system.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	RenderSystem::RenderSystem(
		std::reference_wrapper<const WindowPlatformSupport> windowPlatformSupport,
		std::reference_wrapper<const WindowRendererSupport> windowRendererSupport
	) noexcept
		: mWindowPlatformSupport(windowPlatformSupport)
		, mWindowRendererSupport(windowRendererSupport)
	{
	}

	TOV_NAMESPACE_END // rendering
}