#ifndef TOV_RENDERING_WIN32_GL_RENDER_CONTEXT_H
#define TOV_RENDERING_WIN32_GL_RENDER_CONTEXT_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/render_context.h>

#include <Windows.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class DeviceContext;

	TOV_NAMESPACE_BEGIN(win32)
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
		HGLRC mGLRC;
	};

	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // win32
	TOV_NAMESPACE_END // rendering
}

#endif