#include <rendering/window.h>

#include "rendering/window_platform_support.h"
#include "rendering/window_renderer_support.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	Window::Window(
		const WindowPlatformSupport& platformSupport,
		const WindowRendererSupport& rendererSupport,
		uint width,
		uint height,
		bool fullscreen
	)
		: mPlatformSupport(platformSupport)
		, mRendererSupport(rendererSupport)
		, mWidth(width)
		, mHeight(height)
		, mFullscreen(fullscreen)
	{
		mPlatformComponent = mPlatformSupport.buildComponent(*this);
		mPlatformComponent->create();

		mRendererComponent = mRendererSupport.buildComponent(*this);
	}

	TOV_NAMESPACE_END // rendering
}