#ifndef TOV_RENDERING_RENDER_SYSTEM_H
#define TOV_RENDERING_RENDER_SYSTEM_H

#include "rendering_core.h"

#include "render_target_manager.h"

#include "commands/command_bucket.h"

namespace tov
{
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

        auto createRenderWindow(const char* name, uint width, uint height, bool fullscreen) -> RenderWindow&;

        void swapBuffers();
        void renderFrame();

        auto getGBufferBucket() -> auto& { return mGBufferBucket; }

    private:
        void submit();

    private:
        WindowPlatformSupport& mWindowPlatformSupport;
        WindowRendererSupport& mWindowRendererSupport;

        commands::CommandBucket<128> mGBufferBucket;

        RenderTargetManager mRenderTargetManager;
    };

    TOV_NAMESPACE_END
}

#endif
