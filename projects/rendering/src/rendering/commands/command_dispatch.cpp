#include <rendering/commands/command_dispatch.h>

#include <rendering/commands/commands.h>

#include <rendering/backend.h>

#include <tov/math/matrix.h>

#include <rendering/render_target.h>
#include <rendering/viewport.h>
#include <rendering/mesh/draw_data.h>
#include <rendering/mesh/draw_data_context.h>

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

        /*auto const& modelMatrix = command->modelMatrix;
        auto const& viewMatrix = command->viewMatrix;
        auto const& projectionMatrix = command->projectionMatrix;*/

        //auto const& programInstance = *command->programInstance;
        //programInstance.use();
        /*programInstance.uploadConstants();
        programInstance.uploadConstantData("modelMatrix", modelMatrix.data());
        programInstance.uploadConstantData("viewMatrix", viewMatrix.data());
        programInstance.uploadConstantData("projectionMatrix", projectionMatrix.data());*/

        auto drawData = command->drawData;

        backend::Draw(drawData);
    }

    void CommandDispatch::UploadMVP(const void* data)
    {
        auto command = reinterpret_cast<commands::UploadMVP const* const>(data);

        auto const& modelMatrix = command->modelMatrix;
        auto const& viewMatrix = command->viewMatrix;
        auto const& projectionMatrix = command->projectionMatrix;

        auto const& programInstance = *command->programInstance;
        programInstance.uploadConstantData("modelMatrix", modelMatrix.data());
        programInstance.uploadConstantData("viewMatrix", viewMatrix.data());
        programInstance.uploadConstantData("projectionMatrix", projectionMatrix.data());
    }

    void CommandDispatch::StartDrawDataContext(const void* data)
    {
        auto command = reinterpret_cast<commands::StartDrawDataContext const* const>(data);

        auto drawDataContext = command->drawDataContext;
        drawDataContext->start();
    }

    void CommandDispatch::EndDrawDataContext(const void* data)
    {
        auto command = reinterpret_cast<commands::EndDrawDataContext const* const>(data);

        auto drawDataContext = command->drawDataContext;
        drawDataContext->end();

        delete drawDataContext;
    }

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}
