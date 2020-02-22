#include "rendering_gl/buffers/vertex_buffer_object.h"

#include <iostream>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	VertexBufferObject::VertexBufferObject(
		rendering::buffers::BufferObjectManager& manager,
		rendering::buffers::VertexBufferFormat format,
		uint numVertices
	)
		: mTarget(GL_ARRAY_BUFFER)
		, rendering::buffers::VertexBufferObject<BufferReader, BufferWriter>(
			manager,
			format,
			numVertices,
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

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}
