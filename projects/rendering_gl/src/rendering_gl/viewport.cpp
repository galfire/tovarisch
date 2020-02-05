#include "rendering_gl/viewport.h"

#include "rendering_gl/gl_impl.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)

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
		glEnable(GL_SCISSOR_TEST);

		GLbitfield flags = 0;

		flags |= GL_COLOR_BUFFER_BIT;
		glClearColor(
			mBackgroundColour.r,
			mBackgroundColour.g,
			mBackgroundColour.b,
			mBackgroundColour.a
		);

		flags |= GL_DEPTH_BUFFER_BIT;
		glClearDepth(1.0f);

		flags |= GL_STENCIL_BUFFER_BIT;

		glClear(flags);
	}

	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}