#ifndef TOV_RENDERING_WINIDOW_RENDERER_COMPONENT_H
#define TOV_RENDERING_WINIDOW_RENDERER_COMPONENT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;

	class WindowRendererComponent
	{
	public:
		WindowRendererComponent(Window& parentWindow);
		virtual ~WindowRendererComponent() = default;

	protected:
		Window& mParentWindow;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
