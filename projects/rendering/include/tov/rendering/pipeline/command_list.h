#ifndef TOV_RENDERING_PIPELINE_COMMAND_LIST_H
#define TOV_RENDERING_PIPELINE_COMMAND_LIST_H

#include <tov/rendering/rendering_core.h>

#include <tov/math/matrix.h>
#include <tov/rendering/pipeline/pipeline_state_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    TOV_NAMESPACE_BEGIN(buffers)
    class BufferObject;
    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(mesh)
    class DrawData;
    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_BEGIN(pipeline)
    class PipelineStateObject;
    TOV_NAMESPACE_END // pipeline

    TOV_NAMESPACE_BEGIN(pipeline)

    class PipelineStateObject;

    class CommandList
    {
    public:
        CommandList(PipelineStateObject& pso) noexcept
            : mPSO(&pso)
        {}

        virtual ~CommandList() noexcept = default;

        // Signal the start of the command list
        virtual void reset() TOV_ABSTRACT;

        // Signal the end of the command list
        virtual void close() TOV_ABSTRACT;

        virtual void draw(mesh::DrawData const* const drawData, math::Matrix4 model, math::Matrix4 view, math::Matrix4 projection) TOV_ABSTRACT;
        virtual void setIndexBuffer(buffers::BufferObject* buffer) TOV_ABSTRACT;
        virtual void setVertexBuffers(uint numViews, buffers::BufferObject* buffers) TOV_ABSTRACT;

    private:
        PipelineStateObject* mPSO;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
