#ifndef TOV_RENDERING_PRODUCERS_GBUFFER_PRODUCER_H
#define TOV_RENDERING_PRODUCERS_GBUFFER_PRODUCER_H

#include <tov/rendering/rendering_core.h>

#include "producer.h"

#include <tov/rendering/commands/command_bucket.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;

    TOV_NAMESPACE_BEGIN(pipeline)
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

    class Resource;

    class GBufferProducer
        : public Producer
    {
    public:
        GBufferProducer(RenderSystem& renderSystem, ResourceBucket& resourceBucket) noexcept;
        virtual ~GBufferProducer() noexcept = default;

        auto getCommandBucket() -> auto& { return mCommandBucket; }
        auto getProgramInstance() -> auto& { return mProgramInstance; }

        virtual void setInputs() override;
        virtual void setOutputs() override;
        virtual void render() override;

    private:
        RenderSystem& mRenderSystem;

        commands::CommandBucket<128> mCommandBucket;

        texture::Texture* mTexturePosition = nullptr;
        texture::Texture* mTextureNormal = nullptr;
        texture::Texture* mTextureAlbedo = nullptr;
    };

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}

#endif
