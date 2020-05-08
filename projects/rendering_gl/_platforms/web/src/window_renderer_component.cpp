#include "rendering_gl/window_renderer_component.h"

#include <tov/rendering/window.h>
#include <tov/rendering/window_platform_component.h>

#include "rendering_gl/render_context.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(web)
    TOV_NAMESPACE_BEGIN(gl)

    WindowRendererComponent::WindowRendererComponent(Window& parentWindow)
        : rendering::WindowRendererComponent(parentWindow)
    {}

    void WindowRendererComponent::createRenderContext()
    {
        const DeviceContext& deviceContext = mParentWindow.getPlatformComponent().getDeviceContext();
        mRenderContext = std::unique_ptr<RenderContext>(new RenderContext(deviceContext));
    }

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // web
    TOV_NAMESPACE_END // rendering
}
