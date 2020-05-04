#ifndef TOV_RENDERING_WIN32_DEVICE_CONTEXT_H
#define TOV_RENDERING_WIN32_DEVICE_CONTEXT_H

#include <tov/rendering/rendering_core.h>
#include <tov/rendering/device_context.h>

#include <Windows.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
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
    TOV_NAMESPACE_END // rendering
}

#endif
