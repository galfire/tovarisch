#include "render_window.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<class ViewportT>
	RenderWindow<ViewportT>::RenderWindow(
		const WindowPlatformSupport& platformSupport,
		const WindowRendererSupport& rendererSupport,
		uint width,
		uint height,
		bool fullscreen,
		bool visible,
		PixelFormat pixelFormat
	)
		: RenderTarget(
			width,
			height,
			pixelFormat
		)
		, Window(
			platformSupport,
			rendererSupport,
			width,
			height,
			fullscreen,
			visible,
			pixelFormat
		)
	{
	}

	template<class ViewportT>
	void RenderWindow<ViewportT>::swapBuffers()
	{
		mPlatformComponent->swapBuffers();
	}

	TOV_NAMESPACE_END // rendering
}