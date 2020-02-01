#ifndef TOV_RENDERING_RENDER_TARGET_H
#define TOV_RENDERING_RENDER_TARGET_H

#include "rendering_core.h"

#include "colour.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Camera;
	class Viewport;
	class ViewportFactory;

	class RenderTarget
	{
		TOV_MOVABLE_ONLY(RenderTarget)

	public:
		RenderTarget(
			std::reference_wrapper<const ViewportFactory> viewportFactory,
			uint width,
			uint height
		) noexcept;
		virtual ~RenderTarget() noexcept = default;

		uint getWidth() const noexcept { return mWidth; }
		uint getHeight() const noexcept { return mHeight; }

		void createViewport(
			std::reference_wrapper<const Camera> camera,
			int zIndex,
			float normalizedLeft = 0.0f,
			float normalizedTop = 0.0f,
			float normalizedWidth = 1.0f,
			float normalizedHeight = 1.0f,
			Colour backgroundColour = Colour::Black
		);

	protected:
		std::reference_wrapper<const ViewportFactory> mViewportFactory;

		uint mWidth;
		uint mHeight;

		std::vector<std::unique_ptr<Viewport>> mViewports;
	};

	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_RENDER_TARGET_H
