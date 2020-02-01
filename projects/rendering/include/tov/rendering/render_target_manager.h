#ifndef TOV_RENDERING_RENDER_TARGET_MANAGER_H
#define TOV_RENDERING_RENDER_TARGET_MANAGER_H

#include "rendering_core.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class RenderTarget;

	class RenderTargetManager
	{
	public:
		RenderTargetManager() noexcept = default;
		~RenderTargetManager() noexcept = default;

	private:
		std::vector<std::unique_ptr<RenderTarget>> mRenderTargets;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
