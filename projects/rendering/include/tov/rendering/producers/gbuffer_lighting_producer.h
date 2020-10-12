#ifndef TOV_RENDERING_PRODUCERS_GBUFFER_LIGHTING_PRODUCER_H
#define TOV_RENDERING_PRODUCERS_GBUFFER_LIGHTING_PRODUCER_H

#include <tov/rendering/rendering_core.h>

#include "rendering/producers/producer.h"

#include "rendering/commands/command_bucket.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;

    TOV_NAMESPACE_BEGIN(mesh)
    class Mesh;
    class MeshInstance;
    TOV_NAMESPACE_END // mesh

    TOV_NAMESPACE_BEGIN(pipeline)
    class Framebuffer;
    class Program;
    class ProgramInstance;
    class Shader;
    TOV_NAMESPACE_END // pipeline

    TOV_NAMESPACE_BEGIN(texture)
    class Texture;
    class Texture2D;
    TOV_NAMESPACE_END // texture

    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    class GBufferLightingProducer
        : public Producer
    {
    public:
        GBufferLightingProducer(RenderSystem& renderSystem, ResourceBucket& resourceBucket) noexcept;
        virtual ~GBufferLightingProducer() noexcept = default;

        auto getCommandBucket() const -> auto& { return mCommandBucket; }

        virtual void setInputs() override;
        virtual void setOutputs() override;
        virtual void render() override;

    private:
        RenderSystem& mRenderSystem;

        commands::CommandBucket<32> mCommandBucket;

        pipeline::Framebuffer* mFramebuffer = nullptr;

        pipeline::Program* mProgram;
        pipeline::ProgramInstance* mProgramInstance;

        mesh::Mesh* mFullscreenQuad = nullptr;
        mesh::MeshInstance* mFullscreenQuadInstance = nullptr;
    };

    TOV_NAMESPACE_END // producers
        TOV_NAMESPACE_END // rendering
}

#endif
