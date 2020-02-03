#ifndef TOV_RENDERING_WINDOW_H
#define TOV_RENDERING_WINDOW_H

#include "rendering_core.h"

#include "window_renderer_component.h"
#include "window_platform_component.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformSupport;
	class WindowRendererSupport;

	class Window
	{
	public:
		Window(
			const WindowPlatformSupport& platformSupport,
			const WindowRendererSupport& rendererSupport,
			uint width,
			uint height,
			bool fullscreen
		);
		virtual ~Window() = default;

		uint getWidth() const { return mWidth; }
		uint getHeight() const { return mHeight; }
		bool getFullscreen() const { return mFullscreen; }

	protected:
		const WindowPlatformSupport& mPlatformSupport;
		const WindowRendererSupport& mRendererSupport;
		uint mWidth;
		uint mHeight;
		bool mFullscreen;

		std::unique_ptr<WindowPlatformComponent> mPlatformComponent;
		std::unique_ptr<WindowRendererComponent> mRendererComponent;
	};

	TOV_NAMESPACE_END // rendering
}

#endif