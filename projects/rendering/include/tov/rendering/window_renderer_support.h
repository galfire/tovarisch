#ifndef TOV_RENDERING_WINDOW_RENDERER_SUPPORT_H
#define TOV_RENDERING_WINDOW_RENDERER_SUPPORT_H

#include "rendering_core.h"
#include "window_renderer_component.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;

	class WindowRendererSupport
	{
	public:
		WindowRendererSupport() = default;
		virtual ~WindowRendererSupport() = default;

		auto buildComponent(Window& parentWindow) const -> std::unique_ptr<WindowRendererComponent>
		{
			return std::unique_ptr<WindowRendererComponent>(
				buildComponentImpl(parentWindow)
			);
		}

	private:
		virtual auto buildComponentImpl(Window& parentWindow) const -> WindowRendererComponent *const TOV_ABSTRACT;
	};

	TOV_NAMESPACE_END
}

#endif