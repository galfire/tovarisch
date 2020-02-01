#ifndef TOV_RENDERING_DEVICE_CONTEXT_H
#define TOV_RENDERING_DEVICE_CONTEXT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class DeviceContext
	{
	public:
		DeviceContext() = default;
		virtual ~DeviceContext() = default;
	};

	TOV_NAMESPACE_END // rendering
}

#endif