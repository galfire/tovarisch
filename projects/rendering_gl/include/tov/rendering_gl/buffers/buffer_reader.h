#ifndef TOV_RENDERING_GL_BUFFERS_BUFFER_READER_H
#define TOV_RENDERING_GL_BUFFERS_BUFFER_READER_H

#include <tov/rendering/buffers/buffer_reader.h>

#include "rendering_gl/gl_impl.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	class BufferReader
		: public rendering::buffers::BufferReader<BufferReader>
	{
	public:
		BufferReader(const GLuint& bufferID) noexcept;
		~BufferReader() noexcept = default;

		void readImpl(size_t offset, size_t length, void* pDest);

	private:
		void bindBuffer() const;

	private:
		const GLuint& mBufferID;
		const GLenum mBufferTarget;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_GL_BUFFERS_BUFFER_READER_H
