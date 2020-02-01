#include "rendering_gles/viewport_factory.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gles)

	std::unique_ptr<rendering::Viewport> RenderSystemGLES::createRSViewport(
			std::reference_wrapper<const RenderTarget> renderTarget,
			std::reference_wrapper<const Camera> camera,
			int zIndex,
			float normalizedLeft,
			float normalizedTop,
			float normalizedWidth,
			float normalizedHeight,
			Colour backgroundColour
		) const
	{
		std::unique_ptr<rendering::Viewport> uptr = std::unique_ptr<rendering::Viewport>(
			new Viewport(
				renderTarget,
				camera,
				zIndex,
				normalizedLeft,
				normalizedTop,
				normalizedWidth,
				normalizedHeight,
				backgroundColour
			)
		);

		return uptr;
	}

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}