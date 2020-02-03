#ifndef TOV_RENDERING_RENDER_WINDOW_H
#define TOV_RENDERING_RENDER_WINDOW_H

#include "rendering_core.h"

#include "render_target.h"
#include "window.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<class ViewportT>
	class RenderWindow
		: public RenderTarget<ViewportT>
		, public Window
	{
	public:
		RenderWindow(
			const WindowPlatformSupport& platformSupport,
			const WindowRendererSupport& rendererSupport,
			uint width,
			uint height,
			bool fullscreen
		);
		~RenderWindow() = default;

		void swapBuffers() override;
	private:
	};

	TOV_NAMESPACE_END // rendering
}

#include "tov/rendering/render_window.inl"

#endif