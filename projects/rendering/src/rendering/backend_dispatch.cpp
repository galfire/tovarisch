#include "rendering/backend_dispatch.h"

#include "rendering/backend.h"

#include "rendering/commands/commands.h"

#include "rendering/render_target.h"
#include "rendering/viewport.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    void BackendDispatch::ApplyViewport(const void* data)
    {
        auto command = reinterpret_cast<const commands::ApplyViewport*>(data);
        auto viewport = command->viewport;
        auto& renderTarget = viewport->getRenderTarget();
        renderTarget.prerender();
        backend::ApplyViewport(viewport);
    }

    TOV_NAMESPACE_END // rendering
}
