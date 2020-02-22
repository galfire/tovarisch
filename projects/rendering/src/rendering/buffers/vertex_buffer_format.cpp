#include "rendering/buffers/vertex_buffer_format.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	VertexBufferFormat::VertexBufferFormat(SequenceType sequenceType)
		: mSequenceType(sequenceType)
	{
	}

	void VertexBufferFormat::addAttribute(VertexAttribute attribute)
	{
		mVertexFormat.addAttribute(attribute);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}