#ifndef TOV_RENDERING_WINIDOW_RENDERER_COMPONENT_H
#define TOV_RENDERING_WINIDOW_RENDERER_COMPONENT_H

#include "rendering_core.h"

#include "render_context.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;

	class WindowRendererComponent
	{
	public:
		WindowRendererComponent(Window& parentWindow);
		virtual ~WindowRendererComponent() = default;

		const RenderContext& getRenderContext() const;

		void create();
		void destroy();

	protected:
		virtual void createRenderContext() TOV_ABSTRACT;

	private:
		virtual void _create() TOV_ABSTRACT;
		virtual void _destroy() TOV_ABSTRACT;

	protected:
		Window& mParentWindow;

		std::unique_ptr<RenderContext> mRenderContext;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
