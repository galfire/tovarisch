#ifndef TOV_RENDERING_WINIDOW_RENDERER_COMPONENT_H
#define TOV_RENDERING_WINIDOW_RENDERER_COMPONENT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class DeviceContext;

	class WindowRendererComponent
	{
	public:
		WindowRendererComponent() = default;
		virtual ~WindowRendererComponent() = default;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
