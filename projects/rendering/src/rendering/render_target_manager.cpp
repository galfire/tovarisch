#include "rendering/render_target_manager.h"

#include "rendering/render_target.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    void RenderTargetManager::queueTargets()
    {
        for (auto&& renderTarget : mRenderTargets)
        {
            renderTarget->queueViewports();
            renderTarget->swapBuffers();
        }
    }

    TOV_NAMESPACE_END // rendering
}
