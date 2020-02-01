#ifndef TOV_RENDER_SYSTEM_RENDER_CONTEXT_H
#define TOV_RENDER_SYSTEM_RENDER_CONTEXT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class RenderContext
	{
	public:
		RenderContext() noexcept = default;
		virtual RenderContext() noexcept = default;

		virtual bool makeCurrent() const TOV_ABSTRACT;
	};

	TOV_NAMESPACE_END // rendering
}

#endif