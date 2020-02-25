#ifndef TOV_RENDERING_GLES_GL_IMPL_H
#define TOV_RENDERING_GLES_GL_IMPL_H

#include <tov/core/platform/platform.h>

#if TOV_PLATFORM == TOV_PLATFORM_WIN
#	include <Windows.h>
#endif

#if defined TOV_GLES
#	include <GLES3/gl32.h>
#	include <GLES2/gl2ext.h>
#	include <GLES3/gl3platform.h>
#elif defined TOV_GL
#	include <gl/glew.h>
#	include <gl/GL.h>
#	include <gl/GLU.h>
#endif

#if TOV_DEBUG
#	include <iostream>

	class GLPrinter
	{
	public:
		template<class... U>
		GLPrinter(char* step, U&&... args)
			: mStep(step)
		{
			printStep(mStep, std::forward<U>(args)...);
		}

		~GLPrinter()
		{
			bool success = true;
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) success = false;
			if (success) std::cout << "\tSuccessfully completed " << mStep << ".\n";
			else         std::cout << "\nFailed to complete " << mStep << "!\n";
		}

	private:
		inline void printStep(char* step)
		{
			std::cout << "Performing " << step << "...\t";
		}

		template<class Arg, class... Args>
		inline void printStep(char* step, Arg&& arg, Args&&... args)
		{
			std::cout << "Performing " << step << "(";
			std::cout << std::forward<Arg>(arg);
			((std::cout << ", " << std::forward<Args>(args)), ...);
			std::cout << ")... ";
		}

	private:
		char* mStep;
	};
#endif

template<class... U>
auto log_gl_op(char* step, U&&... args)
{
#if TOV_DEBUG
	return GLPrinter(step, std::forward<U>(args)...);
#else
	return true;
#endif
}

#if TOV_PLATFORM == TOV_PLATFORM_WIN
namespace
{
	inline void GLAPIENTRY MessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam
	)
	{
#if TOV_DEBUG
		auto const src_str = [source]() {
			switch (source)
			{
			case GL_DEBUG_SOURCE_API: return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER: return "OTHER";
			}
		}();

		auto const type_str = [type]() {
			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR: return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
			case GL_DEBUG_TYPE_MARKER: return "MARKER";
			case GL_DEBUG_TYPE_OTHER: return "OTHER";
			}
		}();

		auto const severity_str = [severity]() {
			switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
			case GL_DEBUG_SEVERITY_LOW: return "LOW";
			case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
			case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
			}
		}();

		std::cout << "\n";
		std::cout << src_str << ", " << type_str << ", " << severity_str << ": " << message;
#endif
	}
}
#endif

inline void enableGLOutput()
{
	auto op = log_gl_op("enable GL output");
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#if TOV_PLATFORM == TOV_PLATFORM_WIN
	glDebugMessageCallback(MessageCallback, 0);
#endif
}

#endif
