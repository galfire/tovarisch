#ifndef TOV_RENDERING_PRODUCERS_SKYBOX_PRODUCER_H
#define TOV_RENDERING_PRODUCERS_SKYBOX_PRODUCER_H

#include <tov/rendering/rendering_core.h>

#include "producer.h"

#include <tov/rendering/commands/command_bucket.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;

    TOV_NAMESPACE_BEGIN(mesh)
    class MeshInstance;
    TOV_NAMESPACE_END // mesh

    TOV_NAMESPACE_BEGIN(texture)
    class Texture;
    TOV_NAMESPACE_END // texture

    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    class Resource;

    class SkyboxProducer
        : public Producer
    {
    public:
        SkyboxProducer(RenderSystem& renderSystem, ResourceBucket& resourceBucket) noexcept;
        virtual ~SkyboxProducer() noexcept = default;

        auto getCommandBucket() -> auto& { return mCommandBucket; }
        auto getProgramInstance() -> auto& { return mProgramInstance; }

        virtual void setInputs() override;
        virtual void setOutputs() override;
        virtual void render() override;

    private:
        RenderSystem& mRenderSystem;

        commands::CommandBucket<8> mCommandBucket;

        texture::Texture* mTexture = nullptr;
    };

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}

#endif
