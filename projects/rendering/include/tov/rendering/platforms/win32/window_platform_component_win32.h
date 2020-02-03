#ifndef TOV_RENDERING_PLATFORMS_WEB_WINDOW_PLATFORM_COMPONENT_WIN32_H
#define TOV_RENDERING_PLATFORMS_WEB_WINDOW_PLATFORM_COMPONENT_WIN32_H

#include <rendering/rendering_core.h>

#include <rendering/window_platform_component.h>

#define NOMINMAX
#include <Windows.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;

	TOV_NAMESPACE_BEGIN(platforms)
	TOV_NAMESPACE_BEGIN(win32)

	class WindowPlatformComponentWin32
		: public WindowPlatformComponent
	{
	public:
		WindowPlatformComponentWin32(Window& parentWindow);
		~WindowPlatformComponentWin32() = default;

		void swapBuffers() override;

		void adjustWindow(
			uint clientWidth,
			uint clientHeight,
			uint& outWindowWidth,
			uint& outWindowHeight
		);

	protected:
		void create() override;
		void destroy() override;

		DWORD getWindowStyle(bool fullscreen)
		{
			if(fullscreen)
				return getFullscreenWindowStyle();
			else
				return getWindowedWindowStyle();
		}
		DWORD getFullscreenWindowStyle() { return mFullscreenWindowStyle; }
		DWORD getWindowedWindowStyle() { return mWindowedWindowStyle; }

	protected:
		HWND mHWnd = nullptr;

		DWORD mFullscreenWindowStyle;
		DWORD mWindowedWindowStyle;
	};

	TOV_NAMESPACE_END // win32
	TOV_NAMESPACE_END // platforms
	TOV_NAMESPACE_END // rendering
}

#endif
