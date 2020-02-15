#ifndef TOV_RENDERING_VIEWPORT_H
#define TOV_RENDERING_VIEWPORT_H

#include "rendering_core.h"

#include "colour.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<class ViewportT> class RenderTarget;
	class Camera;

	template<class ViewportT>
	class Viewport
	{
	public:
		explicit inline Viewport(
			const RenderTarget<ViewportT>& renderTarget,
			const Camera& camera,
			int zIndex,
			float normalizedLeft = 0.0f,
			float normalizedTop = 0.0f,
			float normalizedWidth = 1.0f,
			float normalizedHeight = 1.0f,
			Colour backgroundColour = Colour::Black
		) noexcept;
		virtual ~Viewport() noexcept = default;

		void updateDimensions() noexcept;
		
		void apply() const;

		void renderCamera();

		uint getLeft() const { return mLeft; }
		uint getTop() const { return mTop; }
		uint getWidth() const { return mWidth; }
		uint getHeight() const { return mHeight; }

	protected:
		const RenderTarget<ViewportT>& mRenderTarget;
		const Camera& mCamera;

		int mZIndex;

		float mNormalizedLeft;
		float mNormalizedTop;
		float mNormalizedWidth;
		float mNormalizedHeight;

		uint mLeft;
		uint mTop;
		uint mWidth;
		uint mHeight;

		Colour mBackgroundColour;
	};

	TOV_NAMESPACE_END // rendering
}

#include "viewport.inl"

#endif
