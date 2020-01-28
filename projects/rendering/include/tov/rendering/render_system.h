#ifndef TOV_RENDERING_RENDER_SYSTEM_H
#define TOV_RENDERING_RENDER_SYSTEM_H

#include <tov/core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class RenderSystem
	{
	public:
		RenderSystem() noexcept;
		virtual ~RenderSystem() noexcept;
	};

	TOV_NAMESPACE_END
}

#endif