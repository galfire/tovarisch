#include "rendering/render_target_manager.h"

#include "rendering/render_target.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    void RenderTargetManager::renderTargets()
    {
        for (auto&& renderTarget : mRenderTargets)
        {
            renderTarget->renderViewports();
            renderTarget->swapBuffers();
        }
    }

    TOV_NAMESPACE_END // rendering
}
