#ifndef TOV_RENDERING_WINIDOW_PLATFORM_COMPONENT_H
#define TOV_RENDERING_WINIDOW_PLATFORM_COMPONENT_H

#include "rendering_core.h"
#include "device_context.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Window;

    class WindowPlatformComponent
    {
    public:
        WindowPlatformComponent(Window& parentWindow);
        virtual ~WindowPlatformComponent() = default;

        inline auto& getParentWindow() const { return mParentWindow; }
        inline auto const& getDeviceContext() const { return *mDeviceContext.get(); }

        void create();
        void destroy();

        virtual void swapBuffers() TOV_ABSTRACT;

    private:
        virtual void createImpl() TOV_ABSTRACT;
        virtual void destroyImpl() TOV_ABSTRACT;

    protected:
        Window& mParentWindow;

        std::unique_ptr<DeviceContext> mDeviceContext;
        uint mLeft = 0;
        uint mTop = 0;
        uint mColourDepth = 0;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
