#include "rendering/window_factory.h"

#include "rendering/window.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	WindowFactory::WindowFactory(
		std::reference_wrapper<WindowPlatformSupport> windowPlatformSupport,
		std::reference_wrapper<WindowRendererSupport> windowRendererSupport
	)
		: mWindowPlatformSupport(windowPlatformSupport)
		, mWindowRendererSupport(windowRendererSupport)
	{}

	Window* WindowFactory::build(
		std::reference_wrapper<RenderTargetManager> renderTargetManager,
		uint width,
		uint height,
		bool fullscreen
	)
	{
		auto window = std::unique_ptr<Window>();
	}

	TOV_NAMESPACE_END // rendering
}