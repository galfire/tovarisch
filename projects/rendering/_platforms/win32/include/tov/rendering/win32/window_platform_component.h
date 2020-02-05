#ifndef TOV_RENDERING_WIN32_WINDOW_PLATFORM_COMPONENT_H
#define TOV_RENDERING_WIN32_WINDOW_PLATFORM_COMPONENT_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/window_platform_component.h>

#define NOMINMAX
#include <Windows.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Window;

	TOV_NAMESPACE_BEGIN(win32)

	class WindowPlatformComponent
		: public rendering::WindowPlatformComponent
	{
	public:
		WindowPlatformComponent(Window& parentWindow);
		~WindowPlatformComponent() = default;

		void swapBuffers() override;

		void adjustWindow(
			uint clientWidth,
			uint clientHeight,
			uint& outWindowWidth,
			uint& outWindowHeight
		);

	private:
		void _create() override;
		void _destroy() override;

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
		DWORD mFullscreenWindowStyle = 0;
		DWORD mWindowedWindowStyle = 0;
	};

	TOV_NAMESPACE_END // win32
	TOV_NAMESPACE_END // rendering
}

#endif
