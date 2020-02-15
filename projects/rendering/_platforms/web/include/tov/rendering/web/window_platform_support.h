#ifndef TOV_RENDERING_WEB_WINDOW_PLATFORM_SUPPORT_H
#define TOV_RENDERING_WEB_WINDOW_PLATFORM_SUPPORT_H

#include <tov/rendering/rendering_core.h>
#include <tov/rendering/window_platform_support.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class WindowPlatformComponent;

	TOV_NAMESPACE_BEGIN(web)

	class WindowPlatformSupport
		: public rendering::WindowPlatformSupport
	{
	public:
		WindowPlatformSupport() noexcept;
		~WindowPlatformSupport() = default;

		std::unique_ptr<rendering::WindowPlatformComponent> buildComponent(Window& parentWindow) const override;

		void messageHandler() override;
	};

	TOV_NAMESPACE_END // web
	TOV_NAMESPACE_END // rendering
}

#endif
