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

        auto makeCurrent() { return makeCurrentImpl(); }
        auto endCurrent() { return endCurrentImpl(); }
        auto release() { return releaseImpl(); }

    private:
        virtual auto makeCurrentImpl() -> bool TOV_ABSTRACT;
        virtual auto endCurrentImpl() -> bool TOV_ABSTRACT;
        virtual auto releaseImpl() -> bool TOV_ABSTRACT;

    protected:
        const DeviceContext& mDeviceContext;
    };

    TOV_NAMESPACE_END // rendering
}

#endif