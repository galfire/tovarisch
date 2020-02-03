#include "rendering_gles/window_renderer_support.h"

#include "rendering_gles/window_renderer_component.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gles)

	std::unique_ptr<rendering::WindowRendererComponent> WindowRendererSupport::buildComponent(Window& parentWindow) const
	{
		return std::unique_ptr<rendering::WindowRendererComponent>(new WindowRendererComponent(parentWindow));
	}

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}