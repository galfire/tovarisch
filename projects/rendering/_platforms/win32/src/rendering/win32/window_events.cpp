#include "rendering/win32/window_events.h"

#include <tov/rendering/window.h>
#include <tov/rendering/window_platform_component.h>

#include <windowsx.h>
#include <iostream>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(win32)

    void WindowEvents::messageHandler(void)
    {
        MSG msg;
        while(PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    LRESULT CALLBACK WindowEvents::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        auto window = (Window*)nullptr;

        if(msg == WM_CREATE)
        {
            auto lpcs = (LPCREATESTRUCT)lParam;
            auto component = static_cast<WindowPlatformComponent*>(lpcs->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)component);
            window = &component->getParentWindow();
            return 0;
        }
        else
        {
            auto component = (WindowPlatformComponent*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
            if(component)
            {
                window = &component->getParentWindow();
            }
        }

        if(!window)
        {
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }

        switch(msg)
        {
            case WM_ACTIVATE:
            {
                auto active = (LOWORD(wParam) != WA_INACTIVE);
                if (active)
                {
                    //window->setActive(true);
                }
                else
                {
                    //window->setActive(false);
                }
                break;
            }
            case WM_SYSKEYDOWN:
                switch (wParam)
                {
                    case VK_CONTROL:
                    case VK_SHIFT:
                    case VK_MENU:
                        return 0;
                }
                break;
            case WM_SYSKEYUP:
                switch (wParam)
                {
                    case VK_CONTROL:
                    case VK_SHIFT:
                    case VK_MENU:
                    case VK_F10:
                        return 0;
                }
                break;
            case WM_SYSCOMMAND:
            {
                switch (wParam)
                {
                    case SC_SCREENSAVE:
                    case SC_MONITORPOWER:
                        return 0;
                }
                break;
            }
            case WM_SYSCHAR:
                if (wParam != VK_SPACE)
                    return 0;
                break;
            case WM_ENTERSIZEMOVE:
                break;
            case WM_EXITSIZEMOVE:
                break;
            case WM_MOVE:
                //window->windowMovedOrResized();
                break;
            case WM_DISPLAYCHANGE:
                break;
            case WM_SIZE:
                //window->notifyOnResize();
                //window->windowMovedOrResized();
                break;
            case WM_GETMINMAXINFO:
                break;
            case WM_CLOSE:
            {
                /*window->notifyOnClose();
                window->getManager()->destroyRenderWindow(window->getName());*/
                PostQuitMessage(0);
                return 0;
            }

            case WM_LBUTTONDOWN:
                printf("LEFT BUTTON DOWN\n");
                return 0;
            case WM_LBUTTONUP:
                printf("LEFT BUTTON UP\n");
                return 0;

            case WM_MOUSEMOVE:
                auto xPosition = GET_X_LPARAM(lParam);
                auto yPosition = GET_Y_LPARAM(lParam);
                //std::cout << "X: " << xPos    ition << ", Y: " << yPosition << "\n";
        }

        // Pass All Unhandled Messages To DefWindowProc
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}
