#ifndef TOV_RENDERING_WINIDOW_PLATFORM_COMPONENT_H
#define TOV_RENDERING_WINIDOW_PLATFORM_COMPONENT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformComponent
	{
	public:
		WindowPlatformComponent() = default;
		virtual ~WindowPlatformComponent() = default;

		inline std::reference_wrapper<const DeviceContext> getDeviceContext() const
		{
			return std::cref<DeviceContext>(mDeviceContext.get())
		}

	private:
		std::unique_ptr<DeviceContext> mDeviceContext;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
