#include "rendering_gles/viewport.h"

#include "rendering_gles/gl_impl.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gles)

	Viewport::Viewport(
		const RenderTarget<Viewport>& renderTarget,
		const Camera& camera,
		int zIndex,
		float normalizedLeft,
		float normalizedTop,
		float normalizedWidth,
		float normalizedHeight,
		Colour backgroundColour
	)
		: rendering::Viewport<Viewport>(
			renderTarget,
			camera,
			zIndex,
			normalizedLeft,
			normalizedTop,
			normalizedWidth,
			normalizedHeight,
			backgroundColour
		)
	{}

	void Viewport::_apply() const
	{
		GLsizei x, y, w, h;

		x = getLeft();
		y = getTop();
		w = getWidth();
		h = getHeight();

		glViewport(x, y, w, h);

		glScissor(x, y, w, h);
	}

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}