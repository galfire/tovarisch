#ifndef TOV_RENDERING_VIEWPORT_FACTORY_H
#define TOV_RENDERING_VIEWPORT_FACTORY_H

#include "rendering_core.h"

#include "rendering/colour.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Camera;
	class RenderTarget;

	class ViewportFactory
	{
	public:
		virtual std::unique_ptr<Viewport> build(
			std::reference_wrapper<const RenderTarget> renderTarget,
			std::reference_wrapper<const Camera> camera,
			int zIndex,
			float normalizedLeft = 0.0f,
			float normalizedTop = 0.0f,
			float normalizedWidth = 1.0f,
			float normalizedHeight = 1.0f,
			Colour backgroundColour = Colour::Black
		) const TOV_ABSTRACT;
	};

	TOV_NAMESPACE_END // rendering
}

#endif