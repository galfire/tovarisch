#ifndef TOV_RENDERING_RENDER_TARGET_H
#define TOV_RENDERING_RENDER_TARGET_H

#include <tov/core>

#include "definitions.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class RenderTarget
	{
	public:
		RenderTarget(uint width, uint height) noexcept;
		virtual ~RenderTarget() noexcept = default;

	private:
		uint mWidth;
		uint mHeight;
	};

	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_RENDER_TARGET_H
