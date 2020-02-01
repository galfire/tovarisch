#ifndef TOV_RENDERING_GLES_RENDER_SYSTEM_GLES_H
#define TOV_RENDERING_GLES_RENDER_SYSTEM_GLES_H

#include <tov/rendering/render_system.h>
#include <tov/rendering/colour.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformSupport;
	class WindowRendererSupport;

	TOV_NAMESPACE_BEGIN(gles)

	class RenderSystemGLES
		: public RenderSystem
	{
	public:
		RenderSystemGLES(
			std::reference_wrapper<const WindowPlatformSupport> windowPlatformSupport,
			std::reference_wrapper<const WindowRendererSupport> windowRendererSupport
		) noexcept;
	};

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}

#endif