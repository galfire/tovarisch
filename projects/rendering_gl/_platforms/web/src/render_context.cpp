#include "rendering_gl/render_context.h"

#include <iostream>

#include <tov/rendering/web/device_context.h>

#include <emscripten/emscripten.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(web)
	TOV_NAMESPACE_BEGIN(gl)

	RenderContext::RenderContext(const rendering::DeviceContext& deviceContext)
		: rendering::RenderContext(deviceContext)
	{
		const char* canvasID = static_cast<const DeviceContext&>(mDeviceContext).getCanvasID();

		EmscriptenWebGLContextAttributes ctxAttrs;
		emscripten_webgl_init_context_attributes(&ctxAttrs);
		ctxAttrs.majorVersion = 2;
		ctxAttrs.minorVersion = 0;
		mGLRC = emscripten_webgl_create_context(canvasID, &ctxAttrs);
	}

	bool RenderContext::_makeCurrent()
	{
		EMSCRIPTEN_RESULT result = emscripten_webgl_make_context_current(mGLRC);

		switch (result)
		{
		case EMSCRIPTEN_RESULT_SUCCESS:
			std::cout << "MAKE CURRENT SUCCESSFUL\n";
			return true;
		case EMSCRIPTEN_RESULT_DEFERRED:
			std::cout << "EMSCRIPTEN_RESULT_DEFERRED\n";
			break;
		case EMSCRIPTEN_RESULT_NOT_SUPPORTED:
			std::cout << "EMSCRIPTEN_RESULT_NOT_SUPPORTED\n";
			break;
		case EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED:
			std::cout << "EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED\n";
			break;
		case EMSCRIPTEN_RESULT_INVALID_TARGET:
			std::cout << "EMSCRIPTEN_RESULT_INVALID_TARGET\n";
			break;
		case EMSCRIPTEN_RESULT_UNKNOWN_TARGET:
			std::cout << "EMSCRIPTEN_RESULT_UNKNOWN_TARGET\n";
			break;
		case EMSCRIPTEN_RESULT_INVALID_PARAM:
			std::cout << "EMSCRIPTEN_RESULT_INVALID_PARAM\n";
			break;
		case EMSCRIPTEN_RESULT_FAILED:
			std::cout << "EMSCRIPTEN_RESULT_FAILED\n";
			break;
		case EMSCRIPTEN_RESULT_NO_DATA:
			std::cout << "EMSCRIPTEN_RESULT_NO_DATA\n";
			break;
		}
		return false;
	}

	bool RenderContext::_endCurrent()
	{
		//bool success = emscripten_webgl_make_context_current(nullptr);
		//return success;
		return true;
	}

	bool RenderContext::_release()
	{
		bool success = false;
		if(mGLRC)
		{
			success = emscripten_webgl_destroy_context(mGLRC);
			//mGLRC = nullptr;
		}
		return success;
	}

	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // web
	TOV_NAMESPACE_END // rendering
}
