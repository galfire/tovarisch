#ifndef TOV_RENDERING_GL_BUFFERS_VERTEX_BUFFER_OBJECT_H
#define TOV_RENDERING_GL_BUFFERS_VERTEX_BUFFER_OBJECT_H

#include <tov/rendering/buffers/vertex_buffer_object.h>

#include "buffer_reader.h"
#include "buffer_writer.h"

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	class VertexBufferObject
		: public rendering::buffers::VertexBufferObject<BufferReader, BufferWriter>
	{
	public:
		VertexBufferObject(
			rendering::buffers::BufferObjectManager& manager,
			rendering::buffers::VertexBufferFormat format,
			uint numVertices
		);

	private:
		GLuint mBufferID;
		GLenum mTarget;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}

#endif
