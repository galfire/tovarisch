#include "rendering_gl/render_context.h"

#include <tov/rendering/win32/device_context.h>

#include "rendering_gl/gl_impl.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(win32)
    TOV_NAMESPACE_BEGIN(gl)

    HGLRC RenderContext::sSharedGLRC = nullptr;

    RenderContext::RenderContext(const rendering::DeviceContext& deviceContext)
        : rendering::RenderContext(deviceContext)
    {
        HDC hdc = static_cast<const DeviceContext&>(mDeviceContext).getHDC();
        
        int contextattribs[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB,  4,
            WGL_CONTEXT_MINOR_VERSION_ARB,  2,
#if TOV_DEBUG
            WGL_CONTEXT_FLAGS_ARB,          WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
            0
        };

        if (!sSharedGLRC)
        {
            sSharedGLRC = wglCreateContextAttribsARB(hdc, nullptr, contextattribs);
        }

        mGLRC = wglCreateContextAttribsARB(hdc, sSharedGLRC, contextattribs);

        makeCurrent();
        enableGLOutput();
    }

    bool RenderContext::_makeCurrent()
    {
        HDC hdc = static_cast<const DeviceContext&>(mDeviceContext).getHDC();
        bool success = wglMakeCurrent(hdc, sSharedGLRC);
        return success;
    }

    bool RenderContext::_endCurrent()
    {
        bool success = wglMakeCurrent(nullptr, nullptr);
        return success;
    }

    bool RenderContext::_release()
    {
        bool success = false;
        if(mGLRC)
        {
            success = wglDeleteContext(mGLRC);
            mGLRC = nullptr;
        }
        return success;
    }

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // win32
    TOV_NAMESPACE_END // rendering
}
