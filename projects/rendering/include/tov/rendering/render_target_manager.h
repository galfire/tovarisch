#ifndef TOV_RENDERING_RENDER_TARGET_MANAGER_H
#define TOV_RENDERING_RENDER_TARGET_MANAGER_H

#include "rendering_core.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;
    class RenderTarget;

    class RenderTargetManager
    {
    public:
        RenderTargetManager(RenderSystem& renderSystem) noexcept
            : mRenderSystem(renderSystem)
        {}

        ~RenderTargetManager() noexcept = default;

        template<class T, class... U>
        auto create(U&&... args)
        {
            auto renderTarget = std::unique_ptr<T>(
                new T(mRenderSystem, std::forward<U>(args)...)
            );
            mRenderTargets.push_back(std::move(renderTarget));
            auto ret = mRenderTargets.back().get();
            return static_cast<T*>(ret);
        }

        void renderTargets();

    private:
        RenderSystem& mRenderSystem;
        std::vector<std::unique_ptr<RenderTarget>> mRenderTargets;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
