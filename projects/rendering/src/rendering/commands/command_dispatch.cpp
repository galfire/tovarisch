#include <rendering/commands/command_dispatch.h>

#include <rendering/commands/commands.h>

#include <rendering/backend.h>

#include <tov/math/matrix.h>

#include <rendering/render_target.h>
#include <rendering/viewport.h>
#include <rendering/mesh/draw_data.h>
#include <rendering/mesh/draw_data_context.h>
#include <rendering/pipeline/program_instance.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(commands)

    void CommandDispatch::ApplyViewport(const void* data)
    {
        auto command = reinterpret_cast<commands::ApplyViewport const *const>(data);

        const auto viewport = command->viewport;
        const auto& renderTarget = viewport->getRenderTarget();
        renderTarget.prerender();
        backend::ApplyViewport(viewport);
    }

    void CommandDispatch::ClearViewport(const void* data)
    {
        auto command = reinterpret_cast<commands::ApplyViewport const *const>(data);

        auto viewport = command->viewport;
        backend::ClearViewport(viewport);
    }

    void CommandDispatch::Draw(const void* data)
    {
        auto command = reinterpret_cast<commands::Draw const *const>(data);

        auto drawData = command->drawData;
        backend::Draw(drawData);
    }

    void CommandDispatch::SetMVP(const void* data)
    {
        auto command = reinterpret_cast<commands::SetMVP const* const>(data);

        auto const& modelMatrix = command->modelMatrix;
        auto const& viewMatrix = command->viewMatrix;
        auto const& projectionMatrix = command->projectionMatrix;

        auto& programInstance = *command->programInstance;
        programInstance.setConstant("modelMatrix", modelMatrix);
        programInstance.setConstant("viewMatrix", viewMatrix);
        programInstance.setConstant("projectionMatrix", projectionMatrix);
    }

    void CommandDispatch::UploadConstants(const void* data)
    {
        auto command = reinterpret_cast<commands::UploadConstants const* const>(data);

        auto& programInstance = *command->programInstance;
        programInstance.uploadConstants();
    }

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}
