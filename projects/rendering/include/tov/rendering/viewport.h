#ifndef TOV_RENDERING_VIEWPORT_H
#define TOV_RENDERING_VIEWPORT_H

#include "rendering_core.h"

#include "colour.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class RenderTarget;
	class Camera;

	class Viewport
	{
	public:
		explicit Viewport(
			std::reference_wrapper<const RenderTarget> renderTarget,
			std::reference_wrapper<const Camera> camera,
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

		uint getLeft() const { return mLeft; }
		uint getTop() const { return mTop; }
		uint getWidth() const { return mWidth; }
		uint getHeight() const { return mHeight; }

	private:
		virtual void _apply() const TOV_ABSTRACT;

	protected:
		std::reference_wrapper<const RenderTarget> mRenderTarget;
		std::reference_wrapper<const Camera> mCamera;

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

#endif
