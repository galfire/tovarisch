#ifndef TOV_RENDERING_RENDER_SYSTEM_H
#define TOV_RENDERING_RENDER_SYSTEM_H

#include "rendering_core.h"

#include "pixel_format.h"
#include "render_target_manager.h"

#include "commands/command_bucket.h"


namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    TOV_NAMESPACE_BEGIN(buffers)
    class BufferManagerBase;
    class PixelBufferObject;
    TOV_NAMESPACE_END // buffers

    TOV_NAMESPACE_BEGIN(mesh)
    class Mesh;
    class MeshInstance;
    class MeshManager;
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
        virtual ~RenderSystem() noexcept = default;

        auto getWindowPlatformSupport() const -> auto const& { return mWindowPlatformSupport; }
        auto getWindowRendererSupport() const -> auto const& { return mWindowRendererSupport; }

        auto getBufferManager() const { return mBufferManager; }
        auto getMeshManager() const { return mMeshManager; }

        auto createRenderWindow(const char* name, uint width, uint height, bool fullscreen) -> RenderWindow&;
        
        virtual auto createTexture2D(
            rendering::buffers::PixelBufferObject& pbo,
            uint width,
            uint height,
            PixelFormat pixelFormat
        )->texture::Texture2D& TOV_ABSTRACT;

        void initialize();

        void swapBuffers();
        void renderFrame();

        auto getGBufferBucket() -> auto& { return mGBufferBucket; }

        auto getProgramInstanceGBuffer() const { return mProgramInstanceGBuffer; }

    protected:
        RenderTargetManager mRenderTargetManager;

    private:
        WindowPlatformSupport& mWindowPlatformSupport;
        WindowRendererSupport& mWindowRendererSupport;

        buffers::BufferManagerBase* mBufferManager = nullptr;
        mesh::MeshManager* mMeshManager = nullptr;
        mesh::Mesh* mFullscreenQuad = nullptr;
        mesh::MeshInstance* mFullscreenQuadInstance = nullptr;

        commands::CommandBucket<128> mGBufferBucket;
        commands::CommandBucket<32> mGBufferLightingBucket;

        pipeline::Framebuffer* mFramebufferDefault = nullptr;
        pipeline::Framebuffer* mFramebufferGBuffer = nullptr;

        texture::Texture* mTexturePosition = nullptr;
        texture::Texture* mTextureNormal = nullptr;
        texture::Texture* mTextureAlbedo = nullptr;

        pipeline::Program* mProgramGBuffer;
        pipeline::ProgramInstance* mProgramInstanceGBuffer;

        pipeline::Program* mProgramGBufferLighting;
        pipeline::ProgramInstance* mProgramInstanceGBufferLighting;
    };

    TOV_NAMESPACE_END
}

#endif
