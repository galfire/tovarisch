#ifndef TOV_PLATFORMS_WIN32_WINDOW_EVENTS_H
#define TOV_PLATFORMS_WIN32_WINDOW_EVENTS_H

#include "../../rendering_core.h"

#define NOMINMAX
#include <Windows.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(platforms)
	TOV_NAMESPACE_BEGIN(win32)

	class WindowEvents
	{
	public:
		static void	messageHandler(void);
		static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

	TOV_NAMESPACE_END // win32
	TOV_NAMESPACE_END // platforms
	TOV_NAMESPACE_END // rendering
}

#endif
