#ifndef TOV_RENDERING_COMMANDS_COMMANDS_H
#define TOV_RENDERING_COMMANDS_COMMANDS_H

#include <tov/rendering/rendering_core.h>

#include "dispatch_function.h"
#include "command_dispatch.h"

#include <tov/math/matrix.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Viewport;

    TOV_NAMESPACE_BEGIN(pipeline)

    class ProgramInstance;

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData;
    class DrawDataContext;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END //rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(commands)

    struct ApplyViewport
    {
        Viewport const * viewport;
        static inline DispatchFunction DispatchFunction = CommandDispatch::ApplyViewport;
    };

    struct ClearViewport
    {
        Viewport const * viewport;
        static inline DispatchFunction DispatchFunction = CommandDispatch::ClearViewport;
    };

    struct Draw
    {
        math::Matrix4 modelMatrix;
        math::Matrix4 viewMatrix;
        math::Matrix4 projectionMatrix;
        pipeline::ProgramInstance const * programInstance;
        mesh::DrawData const * drawData;
        static inline DispatchFunction DispatchFunction = CommandDispatch::Draw;
    };

    struct StartDrawDataContext
    {
        mesh::DrawDataContext const * drawDataContext;
        static inline DispatchFunction DispatchFunction = CommandDispatch::StartDrawDataContext;
    };

    struct EndDrawDataContext
    {
        mesh::DrawDataContext const * drawDataContext;
        static inline DispatchFunction DispatchFunction = CommandDispatch::EndDrawDataContext;
    };

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}

#endif
