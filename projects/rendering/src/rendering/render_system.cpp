#include "rendering/render_system.h"

#include "rendering/render_window.h"
#include "rendering/window_platform_support.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    RenderSystem::RenderSystem(
        WindowPlatformSupport& windowPlatformSupport,
        WindowRendererSupport& windowRendererSupport
    ) noexcept
        : mRenderTargetManager(*this)
        , mWindowPlatformSupport(windowPlatformSupport)
        , mWindowRendererSupport(windowRendererSupport)
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

    void RenderSystem::renderFrame()
    {
        mWindowPlatformSupport.messageHandler();
        mRenderTargetManager.renderTargets();
        submit();
    }

    void RenderSystem::submit()
    {
        mFrameCommandBucket.submit();
    }

    TOV_NAMESPACE_END // rendering
}