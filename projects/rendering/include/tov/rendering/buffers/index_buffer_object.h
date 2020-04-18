#ifndef TOV_RENDERING_BUFFERS_INDEX_BUFFER_OBJECT_H
#define TOV_RENDERING_BUFFERS_INDEX_BUFFER_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "buffer_object.h"

#include "index_type.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	class BufferBase;

	class IndexBufferObject
		: public BufferObject
	{
	public:
		IndexBufferObject(BufferBase& buffer, uint numIndices)
			: BufferObject(buffer)
			, mNumIndices(numIndices)
			, mIndexType(buffers::getIndexType(numIndices))
		{}

		auto getNumIndices() const { return mNumIndices; }
		auto getIndexType() const { return mIndexType; }

	private:
		uint mNumIndices;
		IndexType mIndexType;
	};

	TOV_NAMESPACE_END // buffers 
	TOV_NAMESPACE_END // rendering
}

#endif
