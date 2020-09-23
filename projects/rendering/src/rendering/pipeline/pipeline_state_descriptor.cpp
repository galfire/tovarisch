#include "rendering/pipeline/pipeline_state_descriptor.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

        PipelineStateDescriptor::PipelineStateDescriptor(
        Program const& program,
        mesh::VertexDataFormat const& vertexDataFormat,
        RasterizerStateDescriptor rasterizerStateDescriptor

    ) noexcept
        : mProgram(program)
        , mVertexDataFormat(vertexDataFormat)
        , mRasterizerStateDescriptor(rasterizerStateDescriptor)
    {
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
