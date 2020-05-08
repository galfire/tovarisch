#ifndef TOV_RENDERING_WEB_GL_WINDOW_RENDERER_COMPONENT_H
#define TOV_RENDERING_WEB_GL_WINDOW_RENDERER_COMPONENT_H

#include <tov/rendering/window_renderer_component.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Window;

    TOV_NAMESPACE_BEGIN(web)
    TOV_NAMESPACE_BEGIN(gl)

    class WindowRendererComponent
        : public rendering::WindowRendererComponent
    {
    public:
        WindowRendererComponent(Window& parentWindow);
        ~WindowRendererComponent() = default;

    private:
        void createImpl() override {}
        void destroyImpl() override {}

        void createRenderContext() override;
    };

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // web
    TOV_NAMESPACE_END // rendering
}

#endif
