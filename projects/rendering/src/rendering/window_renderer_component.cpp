#include <rendering/window_renderer_component.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	WindowRendererComponent::WindowRendererComponent(Window& parentWindow)
		: mParentWindow(parentWindow)
	{}

	TOV_NAMESPACE_END // rendering
}