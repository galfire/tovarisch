#ifndef TOV_RENDERING_RENDER_SYSTEM_H
#define TOV_RENDERING_RENDER_SYSTEM_H

#include "rendering_core.h"

#include "colour.h"
#include "render_target_manager.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    template<class Viewport> class RenderWindow;
    class WindowPlatformSupport;
    class WindowRendererSupport;

    template<class ViewportT>
    class RenderSystem
    {
        using RenderWindowT = RenderWindow<ViewportT>;
        using RenderTargetManagerT = RenderTargetManager<ViewportT>;

    public:
        RenderSystem(
            WindowPlatformSupport& windowPlatformSupport,
            WindowRendererSupport& windowRendererSupport
        ) noexcept;
        ~RenderSystem() noexcept = default;

        auto const& getWindowPlatformSupport() const { return mWindowPlatformSupport; }
        auto const& getWindowRendererSupport() const { return mWindowRendererSupport; }

        auto createRenderWindow(const char* name, uint width, uint height, bool fullscreen);

        void renderFrame();

    private:
        WindowPlatformSupport& mWindowPlatformSupport;
        WindowRendererSupport& mWindowRendererSupport;

        RenderTargetManagerT mRenderTargetManager;
    };

    TOV_NAMESPACE_END
}

#include "render_system.inl"

#endif