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

        auto makeCurrent() { return _makeCurrent(); }
        auto endCurrent() { return _endCurrent(); }
        auto release() { return _release(); }

    private:
        virtual auto _makeCurrent() -> bool TOV_ABSTRACT;
        virtual auto _endCurrent() -> bool TOV_ABSTRACT;
        virtual auto _release() -> bool TOV_ABSTRACT;

    protected:
        const DeviceContext& mDeviceContext;
    };

    TOV_NAMESPACE_END // rendering
}

#endif