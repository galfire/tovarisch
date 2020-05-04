#include "rendering_gl/window_renderer_component.h"

#include <tov/rendering/window.h>
#include <tov/rendering/window_platform_component.h>

#include "rendering_gl/dummy_render_context.h"
#include "rendering_gl/render_context.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(win32)
    TOV_NAMESPACE_BEGIN(gl)

    WindowRendererComponent::WindowRendererComponent(Window& parentWindow)
        : rendering::WindowRendererComponent(parentWindow)
    {}

    void WindowRendererComponent::createRenderContext()
    {
        const DeviceContext& deviceContext = mParentWindow.getPlatformComponent().getDeviceContext();

        static bool dummyCreated = false;
        if(!dummyCreated)
        {
            // Create dummy context to initialize GLEW
            auto dummyContext = std::unique_ptr<DummyRenderContext>(new DummyRenderContext(deviceContext));
            dummyCreated = true;
        }

        mRenderContext = std::unique_ptr<RenderContext>(new RenderContext(deviceContext));
    }

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}
