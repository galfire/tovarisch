#include "rendering/platforms/win32/window_platform_component_win32.h"

#include <algorithm>

#include "rendering/window.h"
#include "rendering/platforms/win32/window_events.h"
#include "rendering/platforms/win32/device_context.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(platforms)
	TOV_NAMESPACE_BEGIN(win32)

	WindowPlatformComponentWin32::WindowPlatformComponentWin32(Window& parentWindow)
		: WindowPlatformComponent(parentWindow)
	{}

	void WindowPlatformComponentWin32::create()
	{
		if(mHWnd)
			destroy();

		const uint16_t moduleFlags =
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
			GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
		LPCSTR moduleName = "";
		HINSTANCE hInstance = nullptr;
		GetModuleHandleEx(moduleFlags, moduleName, &hInstance);

		mColourDepth = GetDeviceCaps(GetDC(0), BITSPIXEL);

		// TODO
		// Get left and top from another optional source
		int top = -1;
		int left = -1;

		const uint width = mParentWindow.getWidth();
		const uint height = mParentWindow.getHeight();
		const bool fullscreen = mParentWindow.getFullscreen();

		char name[] = "WINDOW NAME";

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

		mFullscreenWindowStyle = WS_VISIBLE | WS_CLIPCHILDREN | WS_POPUP;
		mWindowedWindowStyle = WS_VISIBLE | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
		mWindowedWindowStyle ^= WS_THICKFRAME;

		// If no left or top positions have been specified,
		// centre the window
		if(left == -1 || top == -1)
		{
			size_t windowWidth;
			size_t windowHeight;
			adjustWindow(width, height, windowWidth, windowHeight);

			size_t screenWidth = monitorInfoEx.rcWork.right - monitorInfoEx.rcWork.left;
			size_t screenHeight = monitorInfoEx.rcWork.bottom - monitorInfoEx.rcWork.top;

			if(left == -1)
			{
				left = (int)(monitorInfoEx.rcWork.left + (screenWidth - windowWidth) / 2);
			}
			if(top == -1)
			{
				top = (int)(monitorInfoEx.rcWork.top + (screenHeight - windowHeight) / 2);
			}
		}

		mLeft = left;
		mTop = top;

		DWORD dwStyleEx = 0;

		if(fullscreen)
		{
			dwStyleEx |= WS_EX_TOPMOST;
			mLeft = monitorInfoEx.rcWork.left;
			mTop = monitorInfoEx.rcWork.top;
		}
		else
		{
			dwStyleEx |= WS_EX_APPWINDOW;
		}

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

		if(fullscreen)
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

		/*size_t windowNameLen = strlen(name) + 1;
		wchar_t* windowName = new wchar_t[windowNameLen];
		mbstowcs_s(new size_t, windowName, windowNameLen, name, windowNameLen);*/

		mHWnd = CreateWindowEx(
			dwStyleEx,
			"TovarischWindowClass",
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

		//delete windowName;
		//delete[] name;

		HDC hdc = GetDC(mHWnd);
		mDeviceContext = std::make_unique<DeviceContext>(hdc);
	}

	void WindowPlatformComponentWin32::destroy()
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

	void WindowPlatformComponentWin32::swapBuffers()
	{
		DeviceContext* dc = static_cast<DeviceContext*>(mDeviceContext.get());
		HDC hdc = dc->getHDC();
		SwapBuffers(hdc);
	}

	void WindowPlatformComponentWin32::adjustWindow(
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
	TOV_NAMESPACE_END // platforms
	TOV_NAMESPACE_END // rendering
}