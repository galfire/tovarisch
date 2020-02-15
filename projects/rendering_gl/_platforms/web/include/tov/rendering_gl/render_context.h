#ifndef TOV_RENDERING_WEB_GL_RENDER_CONTEXT_H
#define TOV_RENDERING_WEB_GL_RENDER_CONTEXT_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/render_context.h>

#include <emscripten/html5.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class DeviceContext;

	TOV_NAMESPACE_BEGIN(web)
	TOV_NAMESPACE_BEGIN(gl)

	class RenderContext
		: public rendering::RenderContext
	{
	public:
		RenderContext(const rendering::DeviceContext& deviceContext);
		~RenderContext() = default;

	private:
		bool _makeCurrent() override;
		bool _endCurrent() override;
		bool _release() override;

	private:
		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE mGLRC;
	};

	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // web
	TOV_NAMESPACE_END // rendering
}

#endif