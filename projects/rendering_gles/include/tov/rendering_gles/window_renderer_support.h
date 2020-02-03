#ifndef TOV_RENDERING_GLES_WINDOW_RENDERER_SUPPORT_H
#define TOV_RENDERING_GLES_WINDOW_RENDERER_SUPPORT_H

#include <tov/rendering/window_renderer_support.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowRendererComponent;

	TOV_NAMESPACE_BEGIN(gles)

	class WindowRendererSupport
		: public rendering::WindowRendererSupport
	{
	public:
		WindowRendererSupport() = default;
		~WindowRendererSupport() = default;

		std::unique_ptr<rendering::WindowRendererComponent> buildComponent(Window& parentWindow) const override;
	};

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}

#endif