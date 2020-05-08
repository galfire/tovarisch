#include "rendering_gl/dummy_render_context.h"

#include <tov/rendering/win32/device_context.h>

#include "rendering_gl/gl_impl.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(win32)
    TOV_NAMESPACE_BEGIN(gl)

    DummyRenderContext::DummyRenderContext(const rendering::DeviceContext& deviceContext)
        : rendering::RenderContext(deviceContext)
    {
        HDC hdc = static_cast<const DeviceContext&>(mDeviceContext).getHDC();
        mGLRC = wglCreateContext(hdc);

        makeCurrent();

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    }

    auto DummyRenderContext::makeCurrentImpl() -> bool
    {
        HDC hdc = static_cast<const DeviceContext&>(mDeviceContext).getHDC();
        bool success = wglMakeCurrent(hdc, mGLRC);
        return success;
    }

    auto DummyRenderContext::endCurrentImpl() -> bool
    {
        bool success = wglMakeCurrent(nullptr, nullptr);
        return success;
    }

    auto DummyRenderContext::releaseImpl() -> bool
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
