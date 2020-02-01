#ifndef TOV_RENDERING_PLATFORMS_WIN32_DEVICE_CONTEXT_H
#define TOV_RENDERING_PLATFORMS_WIN32_DEVICE_CONTEXT_H

#include <rendering/rendering_core.h>

#include <windef.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(platforms)
	TOV_NAMESPACE_BEGIN(win32)

	class DeviceContext
		: public rendering::DeviceContext
	{
	public:
		DeviceContext(const HDC hdc)
			: rendering::DeviceContext()
			, mHDC(hdc)
		{}
		~DeviceContext() = default;

		const HDC getHDC() const { return mHDC; }

	private:
		const HDC mHDC;
	};

	TOV_NAMESPACE_END // win32
	TOV_NAMESPACE_END // platforms
	TOV_NAMESPACE_END // rendering
}

#endif
