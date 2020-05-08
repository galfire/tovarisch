#ifndef TOV_RENDERING_WEB_WINDOW_PLATFORM_COMPONENT_H
#define TOV_RENDERING_WEB_WINDOW_PLATFORM_COMPONENT_H

#include <tov/rendering/rendering_core.h>
#include <tov/rendering/window_platform_component.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    
    class Window;

    TOV_NAMESPACE_BEGIN(web)

    class WindowPlatformComponent
        : public rendering::WindowPlatformComponent
    {
    public:
        WindowPlatformComponent(Window& window);
        ~WindowPlatformComponent() = default;

        void swapBuffers() override;

    private:
        void createImpl() override;
        void destroyImpl() override;
    };

    TOV_NAMESPACE_END // web
    TOV_NAMESPACE_END // rendering
}

#endif
