#ifndef TOV_RENDERING_RENDER_TARGET_H
#define TOV_RENDERING_RENDER_TARGET_H

#include "rendering_core.h"

#include "colour.h"
#include "pixel_format.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Camera;
	template<class ViewportT> class Viewport;

	template<class ViewportT>
	class RenderTarget
	{
		TOV_MOVABLE_ONLY(RenderTarget)

	public:
		inline RenderTarget(
			uint width,
			uint height,
			PixelFormat pixelFormat = PixelFormat::Default
		) noexcept;
		virtual ~RenderTarget() noexcept = default;

		void renderViewports();
		virtual void prerender() {}

		virtual void swapBuffers() TOV_ABSTRACT;

		inline auto getWidth() const noexcept { return mWidth; }
		inline auto getHeight() const noexcept { return mHeight; }

		inline auto createViewport(
			Camera& camera,
			int zIndex,
			float normalizedLeft = 0.0f,
			float normalizedTop = 0.0f,
			float normalizedWidth = 1.0f,
			float normalizedHeight = 1.0f,
			Colour backgroundColour = Colour::Black
		) -> Viewport<ViewportT>*;

	protected:
		uint mWidth;
		uint mHeight;
		PixelFormat mPixelFormat;

		std::vector<std::unique_ptr<Viewport<ViewportT>>> mViewports;
	};

	TOV_NAMESPACE_END // rendering
}

#include "render_target.inl"

#endif // !TOV_RENDERING_RENDER_TARGET_H
