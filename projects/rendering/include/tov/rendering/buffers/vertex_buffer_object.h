#ifndef TOV_RENDERING_BUFFERS_VERTEX_BUFFER_OBJECT_H
#define TOV_RENDERING_BUFFERS_VERTEX_BUFFER_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "buffer_object.h"

#include "vertex_buffer_format.h"
#include "usage_settings.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class ReaderT, class WriterT>
	class VertexBufferObject
		: BufferObject<ReaderT, WriterT, UsageSettings::WRITE>
	{
	public:
		template<class... U>
		VertexBufferObject(
			BufferObjectManager& manager,
			VertexBufferFormat format,
			uint numVertices,
			U&&... accessorArgs
		)
			: BufferObject(
				manager,
				format.getVertexSize() * numVertices, 
				std::forward<U>(accessorArgs)...
			)
			, mFormat(format)
			, mNumVerticies(numVertices)
		{}

	private:
		VertexBufferFormat mFormat;
		uint mNumVertices;
	};

	TOV_NAMESPACE_END // buffers 
	TOV_NAMESPACE_END // rendering
}

#endif