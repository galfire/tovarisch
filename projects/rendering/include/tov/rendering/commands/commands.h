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

    namespace mesh
    {
        class DrawData;
    }

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
        mesh::DrawData const * drawData;
        static inline DispatchFunction DispatchFunction = CommandDispatch::Draw;
    };

    struct SetMVP
    {
        math::Matrix4 modelMatrix = math::Matrix4::IDENTITY;
        math::Matrix4 viewMatrix = math::Matrix4::IDENTITY;
        math::Matrix4 projectionMatrix = math::Matrix4::IDENTITY;
        pipeline::ProgramInstance* programInstance;
        static inline DispatchFunction DispatchFunction = CommandDispatch::SetMVP;
    };

    struct UploadConstants
    {
        pipeline::ProgramInstance* programInstance;
        static inline DispatchFunction DispatchFunction = CommandDispatch::UploadConstants;
    };

    TOV_NAMESPACE_END // commands
    TOV_NAMESPACE_END // rendering
}

#endif
