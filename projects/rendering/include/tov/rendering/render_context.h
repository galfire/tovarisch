#ifndef TOV_RENDERING_RENDER_CONTEXT_H
#define TOV_RENDERING_RENDER_CONTEXT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class DeviceContext;

	class RenderContext
	{
	public:
		RenderContext(const DeviceContext& deviceContext) noexcept
			: mDeviceContext(deviceContext)
		{}

		virtual ~RenderContext() noexcept = default;

		bool makeCurrent() { return _makeCurrent(); }
		bool endCurrent() { return _endCurrent(); }
		bool release() { return _release(); }

	private:
		virtual bool _makeCurrent() TOV_ABSTRACT;
		virtual bool _endCurrent() TOV_ABSTRACT;
		virtual bool _release() TOV_ABSTRACT;

	protected:
		const DeviceContext& mDeviceContext;
	};

	TOV_NAMESPACE_END // rendering
}

#endif