#include "rendering/window.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	Window::Window(
		std::reference_wrapper<const ViewportFactory> viewportFactory,
		std::reference_wrapper<const WindowPlatformSupport> platformSupport,
		std::reference_wrapper<const WindowRendererSupport> rendererSupport,
		uint width,
		uint height,
		bool fullscreen
	)
		: RenderTarget(
			viewportFactory,
			width,
			height
		)
		, mPlatformSupport(platformSupport)
		, mRendererSupport(rendererSupport)
		, mFullscreen(fullscreen)
	{}

	TOV_NAMESPACE_END // rendering
}