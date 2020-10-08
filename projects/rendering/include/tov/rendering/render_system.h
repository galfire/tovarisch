#ifndef TOV_RENDERING_RENDER_SYSTEM_H
#define TOV_RENDERING_RENDER_SYSTEM_H

#include "rendering_core.h"

#include "render_target_manager.h"

#include "commands/command_bucket.h"


namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)
    class BufferManagerBase;
    class PixelBufferObject;
    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(pipeline)
    class Framebuffer;
    class Program;
    class ProgramInstance;
    class Shader;
    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_BEGIN(texture)
    class Texture2D;
    TOV_NAMESPACE_END // texture
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
        ~RenderSystem() noexcept = default;

        auto getWindowPlatformSupport() const -> auto const& { return mWindowPlatformSupport; }
        auto getWindowRendererSupport() const -> auto const& { return mWindowRendererSupport; }

        auto getBufferManager() const { return mBufferManager; }

        auto createRenderWindow(const char* name, uint width, uint height, bool fullscreen) -> RenderWindow&;

        void initialize();

        void swapBuffers();
        void renderFrame();

        auto getGBufferBucket() -> auto& { return mGBufferBucket; }

        auto getProgramInstanceGBuffer() const { return mProgramInstanceGBuffer; }

    private:
        WindowPlatformSupport& mWindowPlatformSupport;
        WindowRendererSupport& mWindowRendererSupport;

        buffers::BufferManagerBase* mBufferManager = nullptr;

        commands::CommandBucket<128> mGBufferBucket;

        pipeline::Framebuffer* mFramebufferDefault = nullptr;
        pipeline::Framebuffer* mFramebufferGBuffer = nullptr;

        texture::Texture2D* mTexturePosition = nullptr;
        texture::Texture2D* mTextureNormal = nullptr;
        texture::Texture2D* mTextureAlbedo = nullptr;

        pipeline::Program* mProgramGBuffer;
        pipeline::ProgramInstance* mProgramInstanceGBuffer;

        RenderTargetManager mRenderTargetManager;
    };

    TOV_NAMESPACE_END
}

#endif
