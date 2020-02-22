#include "rendering_gl/buffers/buffer_reader.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	BufferReader::BufferReader(const GLuint& bufferID, GLenum target) noexcept
		: mBufferID(bufferID)
		, mBufferTarget(target)
	{
	}

	void BufferReader::readImpl(size_t offset, size_t length, void* pDest)
	{
		bindBuffer();
		//glGetBufferSubData(mBufferTarget, offset, length, pDest);
	}

	void BufferReader::bindBuffer() const
	{
		glBindBuffer(mBufferTarget, mBufferID);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}
