#ifndef TOV_RENDERING_RENDER_TARGET_MANAGER_H
#define TOV_RENDERING_RENDER_TARGET_MANAGER_H

#include "rendering_core.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<class Viewport> class RenderTarget;

	template<class Viewport>
	class RenderTargetManager
	{
		using RenderTargetT = RenderTarget<Viewport>;

	public:
		RenderTargetManager() noexcept = default;
		~RenderTargetManager() noexcept = default;

		template<class T, class... U>
		auto create(U&&... args)
		{
			auto renderTarget = std::unique_ptr<T>(
				new T(std::forward<U>(args)...)
			);
			mRenderTargets.push_back(std::move(renderTarget));
			auto ret = mRenderTargets.back().get();
			return static_cast<T*>(ret);
		}

		void renderTargets()
		{
			for (auto&& renderTarget : mRenderTargets)
			{
				renderTarget->renderViewports();
				renderTarget->swapBuffers();
			}
		}

	private:
		std::vector<std::unique_ptr<RenderTargetT>> mRenderTargets;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
