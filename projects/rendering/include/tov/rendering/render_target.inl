#include "render_target.h"

#include "camera.h"
#include "render_system.h"
#include "viewport.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<class ViewportT>
	inline RenderTarget<ViewportT>::RenderTarget(
		uint width,
		uint height,
		PixelFormat pixelFormat
	) noexcept 
		: mWidth(width)
		, mHeight(height)
		, mPixelFormat(pixelFormat)
	{}

	template<class ViewportT>
	inline Viewport<ViewportT>* RenderTarget<ViewportT>::createViewport(
		const Camera& camera,
		int zIndex,
		float normalizedLeft,
		float normalizedTop,
		float normalizedWidth,
		float normalizedHeight,
		Colour backgroundColour
	)
	{
		auto viewport = std::unique_ptr<ViewportT>(
			new ViewportT(
				*this,
				camera,
				zIndex,
				normalizedLeft,
				normalizedTop,
				normalizedWidth,
				normalizedHeight,
				backgroundColour
			));
		mViewports.push_back(std::move(viewport));
		return mViewports.back().get();
	}

	TOV_NAMESPACE_END
}