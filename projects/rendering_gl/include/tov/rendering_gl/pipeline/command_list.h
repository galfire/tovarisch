#ifndef TOV_RENDERING_GL_PIPELINE_COMMAND_LIST_H
#define TOV_RENDERING_GL_PIPELINE_COMMAND_LIST_H

#include <tov/rendering/pipeline/command_list.h>

#include "rendering/commands/commands.h"

#include <tov/rendering/commands/command_bucket.h>

#include <tov/rendering_gl/gl_backend.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    class CommandList
        : public rendering::pipeline::CommandList
    {
    public:
        CommandList(rendering::pipeline::PipelineStateObject& pso) noexcept
            : rendering::pipeline::CommandList(pso)
        {}

        ~CommandList() noexcept = default;

        // Signal the start of the command list
        void reset() override
        {
        }

        // Signal the end of the command list
        void close() override
        {
        }

        void draw(
            mesh::DrawData const* const drawData,
            math::Matrix4 model,
            math::Matrix4 view,
            math::Matrix4 projection
        ) override
        {
            auto& command = mCommandBucket.addCommand<commands::Draw>(0);
            command.modelMatrix = model;
            command.viewMatrix = view;
            command.projectionMatrix = projection;
            command.drawData = &drawData;
        }
        
        void setIndexBuffer(buffers::BufferObject* buffer) override
        {
        }

        void setVertexBuffers(uint numViews, buffers::BufferObject* buffers) override
        {
        }

        void submit()
        {
            backend::gl::SetRasterizerState(mPSO.getRasterizerStateDescriptor());

            mCommandBucket.submit();
        }

    private:
        rendering::pipeline::PipelineStateObject& mPSO;

        buffers::BufferObject* mIndexBufferObject;

        uint mNumVertexBufferObjects = 0;
        buffers::BufferObject* mVertexBufferObjects;

        commands::CommandBucket<128> mCommandBucket;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
