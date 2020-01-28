#ifndef TOV_RENDERING_VIEWPORT_H
#define TOV_RENDERING_VIEWPORT_H

#include <tov/core.h>

#include "colour.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class RenderTarget;
	class Camera;

	class Viewport
	{
	public:
		Viewport(
			RenderTarget* renderTarget,
			Camera* camera,
			int zIndex,
			// TODO: Replace top and left with a single 2 float point
			float left = 0.0f,
			float top = 0.0f,
			float width = 1.0f,
			float height = 1.0f,
			Colour backgroundColour = Colour::Black
		) noexcept;

		~Viewport() noexcept;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
