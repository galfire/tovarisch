#include "render_window.h"

#include "window_platform_support.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<class ViewportT>
	RenderSystem<ViewportT>::RenderSystem(
		WindowPlatformSupport& windowPlatformSupport,
		WindowRendererSupport& windowRendererSupport
	) noexcept
		: mWindowPlatformSupport(windowPlatformSupport)
		, mWindowRendererSupport(windowRendererSupport)
	{}

	template<class ViewportT>
	auto RenderSystem<ViewportT>::createRenderWindow(const char* name, uint width, uint height, bool fullscreen)
	{
		return mRenderTargetManager.template create<RenderWindowT>(
			mWindowPlatformSupport,
			mWindowRendererSupport,
			name,
			width,
			height,
			fullscreen
		);
	}

	template<class ViewportT>
	void RenderSystem<ViewportT>::renderFrame()
	{
		mWindowPlatformSupport.messageHandler();
		mRenderTargetManager.renderTargets();
	}

	TOV_NAMESPACE_END // rendering
}