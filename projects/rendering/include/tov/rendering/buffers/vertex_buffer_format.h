#ifndef TOV_RENDERING_VERTEX_BUFFER_FORMAT_H
#define TOV_RENDERING_VERTEX_BUFFER_FORMAT_H

#include <tov/rendering/rendering_core.h>

#include "vertex_format.h"
#include "vertex_attribute.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	class VertexBufferFormat
	{
	public:
		enum class SequenceType
		{
			// VNCVNCVNC
			INTERLEAVED,
			// VVVNNNCCC
			SEQUENTIAL
		};

	public:
		VertexBufferFormat() = default;
		VertexBufferFormat(SequenceType sequenceType, VertexFormat vertexFormat);
		~VertexBufferFormat() = default;

		auto getSequenceType() const { return mSequenceType; }
		auto getVertexFormat() const { return mVertexFormat; }

	private:
		SequenceType mSequenceType;

		VertexFormat mVertexFormat;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif