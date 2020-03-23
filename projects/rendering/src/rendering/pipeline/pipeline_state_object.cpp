#include "rendering/pipeline/pipeline_state_object.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    PipelineStateObject::PipelineStateObject(
        Program const& program,
        mesh::VertexDataFormat const& vertexDataFormat
    ) noexcept
        : mProgram(program)
        , mVertexDataFormat(vertexDataFormat)
    {
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
