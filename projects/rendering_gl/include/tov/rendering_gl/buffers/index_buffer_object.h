#ifndef TOV_RENDERING_GL_BUFFERS_INDEX_BUFFER_OBJECT_H
#define TOV_RENDERING_GL_BUFFERS_INDEX_BUFFER_OBJECT_H

#include <tov/rendering/buffers/index_buffer_object.h>

#include "buffer_reader.h"
#include "buffer_writer.h"

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	class IndexBufferObject
		: public rendering::buffers::IndexBufferObject<BufferReader, BufferWriter>
	{
	public:
		IndexBufferObject(
			rendering::buffers::BufferObjectManager& manager,
			rendering::buffers::IndexType indexType,
			uint numIndices
		)
			: mTarget(GL_ELEMENT_ARRAY_BUFFER)
			, rendering::buffers::IndexBufferObject<BufferReader, BufferWriter>(
				manager,
				indexType,
				numIndices,
				mBufferID,
				mTarget
			)
		{
			glGenBuffers(1, &mBufferID);

			GLenum usage;
			if ((USAGE_SETTINGS & tov::rendering::buffers::UsageSettings::STATIC) != 0)
			{
				usage = GL_STATIC_DRAW;
			}
			else
			{
				usage = GL_DYNAMIC_DRAW;
			}
			//glNamedBufferData(mBufferID, mBytes, nullptr, usage);
			glBufferData(mTarget, mBytes, nullptr, usage);
		}

	private:
		GLuint mBufferID;
		GLenum mTarget;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}

#endif
