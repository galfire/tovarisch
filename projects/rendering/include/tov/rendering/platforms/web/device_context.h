#ifndef TOV_RENDERING_PLATFORMS_WEB_DEVICE_CONTEXT_H
#define TOV_RENDERING_PLATFORMS_WEB_DEVICE_CONTEXT_H

#include <rendering/rendering_core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class DeviceContext

	TOV_NAMESPACE_BEGIN(platforms)
	TOV_NAMESPACE_BEGIN(web)

	class DeviceContext
		: public rendering::DeviceContext
	{
	public:
		DeviceContext(const char* canvasID)
			: rendering::DeviceContext()
			, mCanvasID(canvasID)
		{}
		~DeviceContext() = default;

		const char* getCanvasID() const { return mCanvasID; }
		
	private:
		const char* mCanvasID;
	};

	TOV_NAMESPACE_END // web
	TOV_NAMESPACE_END // platforms
	TOV_NAMESPACE_END // rendering
}

#endif