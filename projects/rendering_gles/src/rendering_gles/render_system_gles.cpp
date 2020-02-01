#include "rendering_gles/render_system_gles.h"
#include "rendering_gles/viewport.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gles)

	RenderSystemGLES::RenderSystemGLES(
		std::reference_wrapper<const WindowPlatformSupport> windowPlatformSupport,
		std::reference_wrapper<const WindowRendererSupport> windowRendererSupport
	) noexcept
		: RenderSystem(windowPlatformSupport, windowRendererSupport)
	{
	}

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}
