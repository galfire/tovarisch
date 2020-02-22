#include "rendering_gl/render_context.h"

#include <tov/rendering/win32/device_context.h>

#include "rendering_gl/gl_impl.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(win32)
	TOV_NAMESPACE_BEGIN(gl)

	RenderContext::RenderContext(const rendering::DeviceContext& deviceContext)
		: rendering::RenderContext(deviceContext)
	{
		HDC hdc = static_cast<const DeviceContext&>(mDeviceContext).getHDC();
		mGLRC = wglCreateContext(hdc);

		{
			_makeCurrent();
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				/* Problem: glewInit failed, something is seriously wrong. */
				fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			}
			fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
		}
	}

	bool RenderContext::_makeCurrent()
	{
		HDC hdc = static_cast<const DeviceContext&>(mDeviceContext).getHDC();
		bool success = wglMakeCurrent(hdc, mGLRC);
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
