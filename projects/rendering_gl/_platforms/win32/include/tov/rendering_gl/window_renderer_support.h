#ifndef TOV_RENDERING_WIN32_GL_WINDOW_RENDERER_SUPPORT_H
#define TOV_RENDERING_WIN32_GL_WINDOW_RENDERER_SUPPORT_H

#include <tov/rendering/window_renderer_support.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class WindowRendererComponent;

    TOV_NAMESPACE_BEGIN(win32)
    TOV_NAMESPACE_BEGIN(gl)

    class WindowRendererSupport
        : public rendering::WindowRendererSupport
    {
    public:
        WindowRendererSupport() = default;
        ~WindowRendererSupport() = default;

    private:
        auto buildComponentImpl(Window& parentWindow) const -> rendering::WindowRendererComponent *const override;
    };

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}

#endif
