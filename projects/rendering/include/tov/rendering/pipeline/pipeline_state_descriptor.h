#ifndef TOV_RENDERING_PIPELINE_PIPELINE_STATE_DESCRIPTOR_H
#define TOV_RENDERING_PIPELINE_PIPELINE_STATE_DESCRIPTOR_H

#include <tov/rendering/rendering_core.h>

#include "rasterizer_state_descriptor.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class VertexDataFormat;

    TOV_NAMESPACE_END // mesh

    TOV_NAMESPACE_BEGIN(pipeline)

    class Program;

    class PipelineStateDescriptor
    {
    public:
        PipelineStateDescriptor(
            Program const& program,
            mesh::VertexDataFormat const& vertexDataFormat,
            RasterizerStateDescriptor rasterizerStateDescriptor
        ) noexcept;

        ~PipelineStateDescriptor() noexcept = default;

    private:
        Program const& mProgram;
        mesh::VertexDataFormat const& mVertexDataFormat;
        RasterizerStateDescriptor mRasterizerStateDescriptor;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
