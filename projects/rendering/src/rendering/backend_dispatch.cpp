#include "rendering/backend_dispatch.h"

#include "rendering/backend.h"

#include "rendering/commands/commands.h"

#include <tov/math/matrix.h>

#include "rendering/render_target.h"
#include "rendering/viewport.h"
#include "rendering/mesh/draw_data.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    void BackendDispatch::ApplyViewport(const void* data)
    {
        auto command = reinterpret_cast<commands::ApplyViewport const *const>(data);
        const auto viewport = command->viewport;
        const auto& renderTarget = viewport->getRenderTarget();
        renderTarget.prerender();
        backend::ApplyViewport(viewport);
    }

    void BackendDispatch::ClearViewport(const void* data)
    {
        auto command = reinterpret_cast<commands::ApplyViewport const *const>(data);
        auto viewport = command->viewport;
        backend::ClearViewport(viewport);
    }

    void BackendDispatch::Draw(const void* data)
    {
        auto command = reinterpret_cast<commands::Draw const *const>(data);

        auto const& modelMatrix = command->modelMatrix;
        auto const& viewMatrix = command->viewMatrix;
        auto const& projectionMatrix = command->projectionMatrix;

        auto drawData = command->drawData;
        auto& programInstance = drawData->getProgramInstance();

        programInstance.setMatrix4("modelMatrix", modelMatrix);
        programInstance.setMatrix4("viewMatrix", viewMatrix);
        programInstance.setMatrix4("projectionMatrix", projectionMatrix);

        backend::Draw(drawData);
    }

    TOV_NAMESPACE_END // rendering
}
