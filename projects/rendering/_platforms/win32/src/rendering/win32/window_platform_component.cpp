#include "rendering/win32/window_platform_component.h"

#include <algorithm>

#include <tov/rendering/pixel_format.h>
#include <tov/rendering/window.h>

#include "rendering/win32/device_context.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(win32)

    WindowPlatformComponent::WindowPlatformComponent(Window& parentWindow, const char* windowClassName)
        : rendering::WindowPlatformComponent(parentWindow)
        , mWindowClassName(windowClassName)
    {}

    void WindowPlatformComponent::createImpl()
    {
        if(mHWnd)
            destroy();

        const char* name = mParentWindow.getName();
        const uint width = mParentWindow.getWidth();
        const uint height = mParentWindow.getHeight();
        const bool fullscreen = mParentWindow.getFullscreen();
        const bool visible = mParentWindow.getVisible();
        const PixelFormat pixelFormat = mParentWindow.getPixelFormat();

        const uint16_t moduleFlags =
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
        HINSTANCE hInstance = nullptr;
        GetModuleHandleEx(moduleFlags, nullptr, &hInstance);

        mColourDepth = GetDeviceCaps(GetDC(0), BITSPIXEL);

        // TODO
        // Get left and top from another optional source
        int top = -1;
        int left = -1;

        // Get the default primary monitor
        POINT windowAnchorPoint;
        windowAnchorPoint.x = left;
        windowAnchorPoint.y = top;
        HMONITOR hMonitor = MonitorFromPoint(windowAnchorPoint, MONITOR_DEFAULTTOPRIMARY);

        // Get the target monitor info
        MONITORINFOEX monitorInfoEx;
        memset(&monitorInfoEx, 0, sizeof(MONITORINFOEX));
        monitorInfoEx.cbSize = sizeof(MONITORINFOEX);
        GetMonitorInfo(hMonitor, &monitorInfoEx);

        /*size_t deviceNameLength = wcslen(monitorInfoEx.szDevice) + 1;
        char* deviceName = new char[deviceNameLength];
        wcstombs_s(new size_t, deviceName, deviceNameLength, monitorInfoEx.szDevice, deviceNameLength);
        mDeviceName = std::move(deviceName);
        delete[] deviceName;*/

        mFullscreenWindowStyle = WS_CLIPCHILDREN | WS_POPUP;
        mWindowedWindowStyle = WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
        mWindowedWindowStyle ^= WS_THICKFRAME;
        if (visible)
        {
            mFullscreenWindowStyle |= WS_VISIBLE;
            mWindowedWindowStyle |= WS_VISIBLE;
        }

        // If no left or top positions have been specified,
        // centre the window
        if (left == -1 || top == -1)
        {
            size_t windowWidth;
            size_t windowHeight;
            adjustWindow(width, height, windowWidth, windowHeight);

            size_t screenWidth = monitorInfoEx.rcWork.right - monitorInfoEx.rcWork.left;
            size_t screenHeight = monitorInfoEx.rcWork.bottom - monitorInfoEx.rcWork.top;

            if (left == -1)
            {
                left = (int)(monitorInfoEx.rcWork.left + (screenWidth - windowWidth) / 2);
            }
            if (top == -1)
            {
                top = (int)(monitorInfoEx.rcWork.top + (screenHeight - windowHeight) / 2);
            }
        }

        mLeft = left;
        mTop = top;

        DWORD dwStyleEx = 0;

        if (fullscreen)
        {
            dwStyleEx |= WS_EX_TOPMOST;
            mLeft = monitorInfoEx.rcWork.left;
            mTop = monitorInfoEx.rcWork.top;
        }
        else
        {
            dwStyleEx |= WS_EX_APPWINDOW;
        }

        if (fullscreen)
        {
            DEVMODE dmScreenSettings;
            memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
            dmScreenSettings.dmSize = sizeof(dmScreenSettings);
            dmScreenSettings.dmPelsWidth = (DWORD)width;
            dmScreenSettings.dmPelsHeight = (DWORD)height;
            dmScreenSettings.dmBitsPerPel = (DWORD)mColourDepth;
            dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

            if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
            {
                // Critical Error
            }
        }

        mHWnd = CreateWindowEx(
            dwStyleEx,
            mWindowClassName,
            name,
            getWindowStyle(fullscreen),
            (int)mLeft,
            (int)mTop,
            (int)width,
            (int)height,
            nullptr,
            nullptr,
            hInstance,
            this
        );

        HDC hdc = GetDC(mHWnd);
        mDeviceContext = std::make_unique<DeviceContext>(hdc);

        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.cColorBits = pixelFormat.getBitsColour();
        pfd.cAlphaBits = pixelFormat.getBitsAlpha();
        pfd.cDepthBits = pixelFormat.getBitsDepth();
        pfd.cStencilBits = pixelFormat.getBitsStencil();
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;

        int format = ChoosePixelFormat(hdc, &pfd);
        if (format != 0)
        {
            SetPixelFormat(hdc, format, &pfd);
        }
    }

    void WindowPlatformComponent::destroyImpl()
    {
        if (!mHWnd)
            return;

        bool fullscreen = mParentWindow.getFullscreen();
        if (fullscreen)
        {
            //ChangeDisplaySettingsEx((LPCWSTR)mDeviceName.c_str(), nullptr, nullptr, 0, nullptr);
        }
        DestroyWindow(mHWnd);

        mHWnd = nullptr;
    }

    void WindowPlatformComponent::swapBuffers()
    {
        DeviceContext* dc = static_cast<DeviceContext*>(mDeviceContext.get());
        HDC hdc = dc->getHDC();
        SwapBuffers(hdc);
    }

    void WindowPlatformComponent::adjustWindow(
        uint clientWidth,
        uint clientHeight,
        uint& outWindowWidth,
        uint& outWindowHeight
    )
    {
        bool fullscreen = mParentWindow.getFullscreen();

        RECT rc;
        SetRect(&rc, 0, 0, (int)clientWidth, (int)clientHeight);
        DWORD windowStyle = getWindowStyle(fullscreen);
        AdjustWindowRect(&rc, windowStyle, false);
        outWindowWidth = rc.right - rc.left;
        outWindowHeight = rc.bottom - rc.top;

        HMONITOR hMonitor = MonitorFromWindow(mHWnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFOEX monitorInfoEx;
        memset(&monitorInfoEx, 0, sizeof(MONITORINFOEX));
        monitorInfoEx.cbSize = sizeof(MONITORINFOEX);
        GetMonitorInfo(hMonitor, &monitorInfoEx);

        LONG maxWidth = monitorInfoEx.rcWork.right - monitorInfoEx.rcWork.left;
        LONG maxHeight = monitorInfoEx.rcWork.top - monitorInfoEx.rcWork.bottom;
        outWindowWidth = std::min(outWindowWidth, (size_t)maxWidth);
        outWindowHeight = std::min(outWindowHeight, (size_t)maxHeight);
    }

    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}
