#include <rendering/window_renderer_component.h>

#include <rendering/render_context.h>

#include <cassert>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	WindowRendererComponent::WindowRendererComponent(Window& parentWindow)
		: mParentWindow(parentWindow)
	{}

	const RenderContext& WindowRendererComponent::getRenderContext() const
	{
		return *mRenderContext.get();
	}

	void WindowRendererComponent::create()
	{
		createRenderContext();
		bool success = mRenderContext->makeCurrent();
		assert(success);
	}

	void WindowRendererComponent::destroy()
	{
		// ???
	}

	TOV_NAMESPACE_END // rendering
}