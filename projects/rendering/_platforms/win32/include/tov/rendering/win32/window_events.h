#ifndef TOV_RENDERING_WIN32_WINDOW_EVENTS_H
#define TOV_RENDERING_WIN32_WINDOW_EVENTS_H

#include <tov/rendering/rendering_core.h>

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

#define NOMINMAX
#include <Windows.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(win32)

    class WindowEvents
    {
    public:
        static void	messageHandler(void);
        static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    };

    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}

#endif
