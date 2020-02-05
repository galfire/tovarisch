#ifndef TOV_RENDERING_WINDOW_FACTORY_H
#define TOV_RENDERING_WINDOW_FACTORY_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class RenderTargetManager;
	class Viewport;
	template<class ViewportT> class Window;
	class WindowPlatformSupport;
	class WindowRendererSupport;

	class WindowFactory
	{
	public:
		WindowFactory(
			std::reference_wrapper<WindowPlatformSupport> windowPlatformSupport,
			std::reference_wrapper<WindowRendererSupport> windowRendererSupport
		);
		~WindowFactory() = default;

		Window<Viewport>* build(
			std::reference_wrapper<RenderTargetManager> renderTargetManager,
			uint width,
			uint height,
			bool fullscreen
		);

	private:
		std::reference_wrapper<WindowPlatformSupport> mWindowPlatformSupport;
		std::reference_wrapper<WindowRendererSupport> mWindowRendererSupport;
	};

	TOV_NAMESPACE_END // rendering
}

#endif