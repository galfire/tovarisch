#include "rendering_gles/window_renderer_component.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gles)

	WindowRendererComponent::WindowRendererComponent(Window& parentWindow)
		: rendering::WindowRendererComponent(parentWindow)
	{}

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}