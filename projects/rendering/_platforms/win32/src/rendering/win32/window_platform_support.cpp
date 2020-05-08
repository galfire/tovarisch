#include "rendering/win32/window_platform_support.h"

#include "rendering/win32/window_platform_component.h"
#include "rendering/win32/window_events.h"

#include <Windows.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(win32)

    WindowPlatformSupport::WindowPlatformSupport()
    {
        registerWndClasses();
    }

    std::unique_ptr<rendering::WindowPlatformComponent> WindowPlatformSupport::buildComponent(Window& parentWindow) const
    {
        return std::unique_ptr<rendering::WindowPlatformComponent>(
            new WindowPlatformComponent(parentWindow, "TovarischWindowClass")
        );
    }

    void WindowPlatformSupport::messageHandler()
    {
        WindowEvents::messageHandler();
    }

    void WindowPlatformSupport::registerWndClasses() const
    {
        const uint16_t moduleFlags =
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
        HINSTANCE hInstance = nullptr;
        GetModuleHandleEx(moduleFlags, nullptr, &hInstance);

        // Register main window class
        WNDCLASS wc;
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = WindowEvents::wndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = "TovarischWindowClass";
        RegisterClass(&wc);

        // Register dummy window class
        WNDCLASS dummyClass;
        memset(&dummyClass, 0, sizeof(WNDCLASS));
        dummyClass.style = CS_OWNDC;
        dummyClass.hInstance = hInstance;
        dummyClass.lpfnWndProc = DefWindowProc;
        dummyClass.lpszClassName = "DummyWindowClass";
        RegisterClass(&dummyClass);
    }

    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}
