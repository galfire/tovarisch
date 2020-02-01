#include "rendering_gles/viewport.h"

#include "rendering_gles/gl_impl.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gles)

	void Viewport::_apply() const
	{
		GLsizei x, y, w, h;

		x = viewport->getLeft();
		y = viewport->getTop();
		w = viewport->getWidth();
		h = viewport->getHeight();

		glViewport(x, y, w, h);

		glScissor(x, y, w, h);
	}

	TOV_NAMESPACE_END // gles
	TOV_NAMESPACE_END // rendering
}