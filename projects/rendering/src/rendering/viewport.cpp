#include "rendering/viewport.h"

#include "rendering/render_target.h"
#include "rendering/camera.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	Viewport::Viewport(
		std::reference_wrapper<const RenderTarget> renderTarget,
		std::reference_wrapper<const Camera> camera,
		int zIndex,
		float normalizedLeft,
		float normalizedTop,
		float normalizedWidth,
		float normalizedHeight,
		Colour backgroundColor
	) noexcept
		: mRenderTarget(renderTarget)
		, mCamera(camera)
		, mZIndex(zIndex)
		, mNormalizedLeft(normalizedLeft)
		, mNormalizedTop(normalizedTop)
		, mNormalizedWidth(normalizedWidth)
		, mNormalizedHeight(normalizedHeight)
		, mBackgroundColour(backgroundColor)
		, mLeft(0)
		, mTop(0)
		, mWidth(0)
		, mHeight(0)
	{
		updateDimensions();
	}

	void Viewport::updateDimensions() noexcept
	{
		uint width = mRenderTarget.get().getWidth();
		uint height = mRenderTarget.get().getHeight();

		mLeft = static_cast<uint>(mNormalizedLeft * width);
		mTop = static_cast<uint>(mNormalizedTop * height);
		mWidth = static_cast<uint>(mNormalizedWidth * width);
		mHeight = static_cast<uint>(mNormalizedHeight * height);

		//mCamera.get().setAspectRatio((float)mWidth / float(mHeight));
	}

	void Viewport::apply() const
	{
		this->_apply();
	}

	TOV_NAMESPACE_END
}