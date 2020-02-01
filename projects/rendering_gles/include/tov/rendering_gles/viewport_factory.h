#ifndef TOV_RENDERING_GLES_VIEWPORT_FACTORY_H
#define TOV_RENDERING_GLES_VIEWPORT_FACTORY_H

#include <tov/rendering/colour.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Camera;
	class RenderTarget;

	TOV_NAMESPACE_BEGIN(gles)

	class ViewportFactory
		: public RenderSystem
	{
	public:
		std::unique_ptr<rendering::Viewport> createViewport(
			std::reference_wrapper<const RenderTarget> renderTarget,
			std::reference_wrapper<const Camera> camera,
			int zIndex,
			float normalizedLeft = 0.0f,
			float normalizedTop = 0.0f,
			float normalizedWidth = 1.0f,
			float normalizedHeight = 1.0f,
			Colour backgroundColour = Colour::Black
		) const;
	};

	TOV_NAMESPACE_END // gles
		TOV_NAMESPACE_END // rendering
}

#endif