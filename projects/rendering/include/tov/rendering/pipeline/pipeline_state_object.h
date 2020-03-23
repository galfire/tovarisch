#ifndef TOV_RENDERING_PIPELINE_PIPELINE_STATE_OBJECT_H
#define TOV_RENDERING_PIPELINE_PIPELINE_STATE_OBJECT_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class VertexDataFormat;

    TOV_NAMESPACE_END // mesh

    TOV_NAMESPACE_BEGIN(pipeline)

    class Program;

    class PipelineStateObject
    {
    public:
        PipelineStateObject(
            Program const& program,
            mesh::VertexDataFormat const& vertexDataFormat
        ) noexcept;

        ~PipelineStateObject() noexcept = default;

    private:
        Program const& mProgram;
        mesh::VertexDataFormat const& mVertexDataFormat;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
