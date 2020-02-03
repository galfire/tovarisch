#ifndef TOV_RENDERING_GLES_VIEWPORT_H
#define TOV_RENDERING_GLES_VIEWPORT_H

#include <tov/rendering/viewport.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gles)

	class Viewport
		: public rendering::Viewport<Viewport>
	{
		friend class rendering::Viewport<Viewport>;

	public:
		Viewport(
			const RenderTarget<Viewport>& renderTarget,
			const Camera& camera,
			int zIndex,
			float normalizedLeft = 0.0f,
			float normalizedTop = 0.0f,
			float normalizedWidth = 1.0f,
			float normalizedHeight = 1.0f,
			Colour backgroundColour = Colour::Black
		);
		~Viewport() = default;

	private:
		void _apply() const;
	};

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}

#endif