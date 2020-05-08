#include "rendering_gl/window_renderer_support.h"

#include "rendering_gl/window_renderer_component.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(win32)
    TOV_NAMESPACE_BEGIN(gl)

    auto WindowRendererSupport::buildComponentImpl(Window& parentWindow) const -> rendering::WindowRendererComponent *const
    {
        return new WindowRendererComponent(parentWindow);
    }

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}
