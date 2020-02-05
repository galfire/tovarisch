#ifndef TOV_RENDERING_WIN32_GL_WINDOW_RENDERER_COMPONENT_H
#define TOV_RENDERING_WIN32_GL_WINDOW_RENDERER_COMPONENT_H

#include <tov/rendering/window_renderer_component.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;

	TOV_NAMESPACE_BEGIN(win32)
	TOV_NAMESPACE_BEGIN(gl)

	class WindowRendererComponent
		: public rendering::WindowRendererComponent
	{
	public:
		WindowRendererComponent(Window& parentWindow);
		~WindowRendererComponent() = default;

	private:
		void _create() override {}
		void _destroy() override {}

		void createRenderContext() override;
	};

	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // win32
	TOV_NAMESPACE_END // rendering
}

#endif