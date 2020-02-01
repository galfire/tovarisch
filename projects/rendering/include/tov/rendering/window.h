#ifndef TOV_RENDERING_WINDOW_H
#define TOV_RENDERING_WINDOW_H

#include "rendering_core.h"

#include "render_target.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformComponent;
	class WindowPlatformSupport;
	class WindowRendererComponent;
	class WindowRendererSupport;

	class Window
		: public RenderTarget
	{
	public:
		Window(
			std::reference_wrapper<const ViewportFactory> viewportFactory,
			std::reference_wrapper<const WindowPlatformSupport> platformSupport,
			std::reference_wrapper<const WindowRendererSupport> rendererSupport,
			uint width,
			uint height,
			bool fullscreen
		);
		~Window() = default;

	private:
		std::reference_wrapper<const WindowPlatformSupport> mPlatformSupport;
		std::reference_wrapper<const WindowRendererSupport> mRendererSupport;

		bool mFullscreen;

		std::unique_ptr<WindowPlatformComponent> mPlatformComponent;
		std::unique_ptr<WindowRendererComponent> mRendererComponent;
	};

	TOV_NAMESPACE_END // rendering
}

#endif