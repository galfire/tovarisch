#ifndef TOV_RENDERING_GLES_WINDOW_RENDERER_COMPONENT_H
#define TOV_RENDERING_GLES_WINDOW_RENDERER_COMPONENT_H

#include <tov/rendering/window_renderer_component.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;

	TOV_NAMESPACE_BEGIN(gles)

	class WindowRendererComponent
		: public rendering::WindowRendererComponent
	{
	public:
		WindowRendererComponent(Window& parentWindow);
		~WindowRendererComponent() = default;
	};

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}

#endif