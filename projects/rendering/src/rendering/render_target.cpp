#include "rendering/render_target.h"

#include "rendering/camera.h"
#include "rendering/render_system.h"
#include "rendering/viewport.h"
#include "rendering/viewport_factory.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	RenderTarget::RenderTarget(
		std::reference_wrapper<const ViewportFactory> viewportFactory,
		uint width,
		uint height
	) noexcept 
		: mViewportFactory(viewportFactory)
		, mWidth(width)
		, mHeight(height)
	{}

	void RenderTarget::createViewport(
		std::reference_wrapper<const Camera> camera,
		int zIndex,
		float normalizedLeft,
		float normalizedTop,
		float normalizedWidth,
		float normalizedHeight,
		Colour backgroundColour
	)
	{
		mViewports.push_back(mViewportFactory.get().build(
			*this,
			camera,
			zIndex,
			normalizedLeft,
			normalizedTop,
			normalizedWidth,
			normalizedHeight,
			backgroundColour
		));
	}

	TOV_NAMESPACE_END
}