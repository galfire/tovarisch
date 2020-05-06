#include "rendering/render_target_manager.h"

#include "rendering/render_target.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    RenderTargetManager::RenderTargetManager() noexcept
    {}

    RenderTargetManager::~RenderTargetManager() noexcept
    {}

    void RenderTargetManager::swapBuffers()
    {
        for (auto&& renderTarget : mRenderTargets)
        {
            renderTarget->swapBuffers();
        }
    }

    TOV_NAMESPACE_END // rendering
}
