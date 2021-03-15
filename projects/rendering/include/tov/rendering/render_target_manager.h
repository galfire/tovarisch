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
        RenderTargetManager() noexcept;
        ~RenderTargetManager() noexcept;

        template<class T, class... U>
        auto create(U&&... args)
        {
            {
                auto renderTarget = std::make_unique<T>(std::forward<U>(args)...);
                mRenderTargets.push_back(std::move(renderTarget));
            }

            auto renderTarget = mRenderTargets.back().get();
            return static_cast<T*>(renderTarget);
        }

        void swapBuffers();

    private:
        std::vector<std::unique_ptr<RenderTarget>> mRenderTargets;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
