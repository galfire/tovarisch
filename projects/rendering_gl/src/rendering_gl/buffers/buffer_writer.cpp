#include "rendering_gl/buffers/buffer_writer.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	BufferWriter::BufferWriter(const GLuint& bufferID, GLenum target) noexcept
		: mBufferID(bufferID)
		, mBufferTarget(target)
	{
	}

	void BufferWriter::writeImpl(size_t offset, size_t length, void* pSrc)
	{
		bindBuffer();
		glBufferSubData(mBufferTarget, offset, length, pSrc);
	}

	void BufferWriter::bindBuffer() const
	{
		glBindBuffer(mBufferTarget, mBufferID);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}