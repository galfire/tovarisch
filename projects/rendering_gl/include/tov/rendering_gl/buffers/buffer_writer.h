#ifndef TOV_RENDERING_GL_BUFFER_WRITER_H
#define TOV_RENDERING_GL_BUFFER_WRITER_H

#include <tov/rendering/rendering_core.h>

#include "buffer_binder.h"

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	class BufferWriter
	{
	private:
		auto bind() { return BufferBinder(mBufferID, mBufferTarget); }

	public:
		BufferWriter(void*& src, void*& dst, GLuint& bufferID, GLenum& bufferTarget)
			: mSource(src)
			, mDestination(dst)
			, mBufferID(bufferID)
			, mBufferTarget(bufferTarget)
		{}
		virtual ~BufferWriter() = default;

		void operator () (size_t offset, size_t length)
		{
			auto b = bind();
			auto op = log_gl_op("buffer subdata", mBufferTarget, offset, length, mSource);
			glBufferSubData(mBufferTarget, offset, length, mSource);
		}

	private:
		void*& mSource;
		void*& mDestination;
		GLuint& mBufferID;
		GLenum& mBufferTarget;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}

#endif
