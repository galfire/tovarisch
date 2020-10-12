#ifndef TOV_RENDERING_RENDER_SYSTEM_H
#define TOV_RENDERING_RENDER_SYSTEM_H

#include "rendering_core.h"

#include "pixel_format.h"
#include "render_target_manager.h"

#include "commands/command_bucket.h"

#include "producers/gbuffer_producer.h"


namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    class Scene;

    TOV_NAMESPACE_BEGIN(buffers)
    class BufferManagerBase;
    TOV_NAMESPACE_END // buffers

    TOV_NAMESPACE_BEGIN(mesh)
    class MeshManager;
    TOV_NAMESPACE_END // mesh

    TOV_NAMESPACE_BEGIN(producers)
    class Producer;
    class ResourceBucket;
    TOV_NAMESPACE_END // producers

    TOV_NAMESPACE_END // rendering
        
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderWindow;
    class WindowPlatformSupport;
    class WindowRendererSupport;

    class RenderSystem
    {
    public:
        RenderSystem(
            WindowPlatformSupport& windowPlatformSupport,
            WindowRendererSupport& windowRendererSupport
        ) noexcept;
        virtual ~RenderSystem() noexcept;

        auto getWindowPlatformSupport() const -> auto const& { return mWindowPlatformSupport; }
        auto getWindowRendererSupport() const -> auto const& { return mWindowRendererSupport; }

        auto getBufferManager() const { return mBufferManager.get(); }
        auto getMeshManager() const { return mMeshManager.get(); }

        auto createRenderWindow(const char* name, uint width, uint height, bool fullscreen) -> RenderWindow&;
        
        virtual auto createTexture2D(
            uint width,
            uint height,
            PixelFormat pixelFormat
        ) -> texture::Texture2D& TOV_ABSTRACT;

        void initialize();

        void swapBuffers();
        void renderFrame(Scene& scene);

        auto getGBufferBucket() -> auto& { return mGBufferProducer->getCommandBucket(); }

        auto getProgramInstanceGBuffer() const { return mGBufferProducer->getProgramInstance(); }

    protected:
        RenderTargetManager mRenderTargetManager;

    private:
        WindowPlatformSupport& mWindowPlatformSupport;
        WindowRendererSupport& mWindowRendererSupport;

        std::unique_ptr<buffers::BufferManagerBase> mBufferManager = nullptr;
        std::unique_ptr<mesh::MeshManager> mMeshManager = nullptr;

        std::vector<producers::Producer*> mProducers;
        producers::Producer* mFinalProducer;
        producers::GBufferProducer* mGBufferProducer;
        producers::ResourceBucket* mResourceBucket;
    };

    TOV_NAMESPACE_END
}

#endif
