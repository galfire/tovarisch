#include "rendering/render_system.h"

#include "rendering/render_window.h"
#include "rendering/window_platform_support.h"

#include "rendering/scene.h"

#include "rendering/buffers/buffer_manager.h"
#include "rendering/mesh/mesh_manager.h"

#include "rendering/producers/resource_bucket.h"
#include "rendering/producers/gbuffer_producer.h"
#include "rendering/producers/gbuffer_lighting_producer.h"

#include "rendering/backend.h"


namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    RenderSystem::RenderSystem(
        WindowPlatformSupport& windowPlatformSupport,
        WindowRendererSupport& windowRendererSupport
    ) noexcept
        : mRenderTargetManager()
        , mWindowPlatformSupport(windowPlatformSupport)
        , mWindowRendererSupport(windowRendererSupport)
    {
        mBufferManager = std::unique_ptr<buffers::BufferManagerBase>(
            backend::createBufferManager()
        );
        mMeshManager = std::unique_ptr<mesh::MeshManager>(
            new mesh::MeshManager(*mBufferManager)
        );
    }

    RenderSystem::~RenderSystem() noexcept
    {}

    auto RenderSystem::createRenderWindow(const char* name, uint width, uint height, bool fullscreen) -> RenderWindow&
    {
        auto renderWindow = mRenderTargetManager.template create<RenderWindow>(
            mWindowPlatformSupport,
            mWindowRendererSupport,
            name,
            width,
            height,
            fullscreen
        );
        return *renderWindow;
    }

    void RenderSystem::initialize()
    {
        mResourceBucket = new producers::ResourceBucket();

        auto gbuffer_producer = new producers::GBufferProducer(*this, *mResourceBucket);
        mGBufferProducer = gbuffer_producer;
        mProducers.push_back(gbuffer_producer);

        auto gbuffer_lighting_producer = new producers::GBufferLightingProducer(*this, *mResourceBucket);
        mProducers.push_back(gbuffer_lighting_producer);

        mFinalProducer = gbuffer_lighting_producer;
    }

    void RenderSystem::swapBuffers()
    {
        mRenderTargetManager.swapBuffers();
    }

    void RenderSystem::renderFrame(Scene& scene)
    {
        mWindowPlatformSupport.messageHandler();

        scene.queue();
        
        for (auto&& producer : mProducers)
        {
            producer->setOutputs();
        }

        for (auto&& producer : mProducers)
        {
            producer->setInputs();
        }

        auto dependentProducers = mFinalProducer->getResolvedDependencies();
        for (auto&& dependentProducer : dependentProducers)
        {
            auto producer = static_cast<producers::Producer*>(dependentProducer);
            producer->render();
        }

        //mResourceBucket->reset();
    }

    TOV_NAMESPACE_END // rendering
}
