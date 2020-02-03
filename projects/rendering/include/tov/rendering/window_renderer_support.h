#ifndef TOV_RENDERING_WINDOW_RENDERER_SUPPORT_H
#define TOV_RENDERING_WINDOW_RENDERER_SUPPORT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;
	class WindowRendererComponent;

	class WindowRendererSupport
	{
	public:
		WindowRendererSupport() = default;
		virtual ~WindowRendererSupport() = default;

		virtual std::unique_ptr<WindowRendererComponent> buildComponent(Window& parentWindow) const TOV_ABSTRACT;
	};

	TOV_NAMESPACE_END
}

#endif