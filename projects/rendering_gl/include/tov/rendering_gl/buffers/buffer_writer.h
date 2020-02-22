#ifndef TOV_RENDERING_GL_BUFFERS_BUFFER_WRITER_H
#define TOV_RENDERING_GL_BUFFERS_BUFFER_WRITER_H

#include <tov/rendering/buffers/buffer_writer.h>

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	class BufferWriter
		: public rendering::buffers::BufferWriter<BufferWriter>
	{
	public:
		BufferWriter(const GLuint& bufferID, GLenum target) noexcept;
		~BufferWriter() noexcept = default;

		void writeImpl(size_t offset, size_t length, void* pSrc);

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
