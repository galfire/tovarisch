#ifndef TOV_RENDERING_RENDER_TARGET_H
#define TOV_RENDERING_RENDER_TARGET_H

#include "rendering_core.h"

#include "colour.h"

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
			uint height
		) noexcept;
		virtual ~RenderTarget() noexcept = default;

		virtual void swapBuffers() TOV_ABSTRACT;

		uint getWidth() const noexcept { return mWidth; }
		uint getHeight() const noexcept { return mHeight; }

		inline Viewport<ViewportT>* createViewport(
			const Camera& camera,
			int zIndex,
			float normalizedLeft = 0.0f,
			float normalizedTop = 0.0f,
			float normalizedWidth = 1.0f,
			float normalizedHeight = 1.0f,
			Colour backgroundColour = Colour::Black
		);

	protected:
		uint mWidth;
		uint mHeight;

		std::vector<std::unique_ptr<Viewport<ViewportT>>> mViewports;
	};

	TOV_NAMESPACE_END // rendering
}

#include "render_target.inl"

#endif // !TOV_RENDERING_RENDER_TARGET_H
