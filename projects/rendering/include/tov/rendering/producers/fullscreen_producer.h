#ifndef TOV_RENDERING_PRODUCERS_FULLSCREEN_PRODUCER_H
#define TOV_RENDERING_PRODUCERS_FULLSCREEN_PRODUCER_H

#include <tov/rendering/rendering_core.h>

#include "rendering/producers/producer.h"

#include "rendering/commands/command_bucket.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;

    TOV_NAMESPACE_BEGIN(mesh)
    class MeshInstance;
    TOV_NAMESPACE_END // mesh

    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    class FullscreenProducer
        : public Producer
    {
    public:
        FullscreenProducer(RenderSystem& renderSystem, ResourceBucket& resourceBucket) noexcept;
        virtual ~FullscreenProducer() noexcept = default;

        auto getCommandBucket() const -> auto& { return mCommandBucket; }

        virtual void setInputs() override;
        virtual void setOutputs() override;
        virtual void render() override;

    private:
        RenderSystem& mRenderSystem;

        commands::CommandBucket<8> mCommandBucket;

        mesh::MeshInstance* mFullscreenQuadInstance = nullptr;
    };

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}

#endif
