#ifndef TOV_RENDERING_RENDER_SYSTEM_H
#define TOV_RENDERING_RENDER_SYSTEM_H

#include <tov/core.h>

#include "colour.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformSupport;
	class WindowRendererSupport;

	class RenderSystem
	{
	public:
		RenderSystem(
			std::reference_wrapper<const WindowPlatformSupport> windowPlatformSupport,
			std::reference_wrapper<const WindowRendererSupport> windowRendererSupport
		) noexcept;
		virtual ~RenderSystem() noexcept;

		std::reference_wrapper<const WindowPlatformSupport> getWindowPlatformSupport() const { return mWindowPlatformSupport; }
		std::reference_wrapper<const WindowRendererSupport> getWindowRendererSupport() const { return mWindowRendererSupport; }

	private:
		std::reference_wrapper<const WindowPlatformSupport> mWindowPlatformSupport;
		std::reference_wrapper<const WindowRendererSupport> mWindowRendererSupport;
	};

	TOV_NAMESPACE_END
}

#endif