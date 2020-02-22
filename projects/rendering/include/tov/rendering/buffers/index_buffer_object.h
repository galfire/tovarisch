#ifndef TOV_RENDERING_BUFFERS_INDEX_BUFFER_OBJECT_H
#define TOV_RENDERING_BUFFERS_INDEX_BUFFER_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "buffer_object.h"

#include "index_type.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class ReaderT, class WriterT>
	class IndexBufferObject
		: public BufferObject<ReaderT, WriterT, UsageSettings::STATIC, AccessSettings::WRITE>
	{
	private:
		static constexpr size_t getIndexTypeSize(IndexType indexType)
		{
			switch (indexType)
			{
			case IndexType::BITS_8:
				return 8;
			case IndexType::BITS_16:
				return 16;
			case IndexType::BITS_32:
				return 32;
			}
		}

	public:
		template<class... U>
		IndexBufferObject(
			BufferObjectManager& manager,
			IndexType indexType,
			uint numIndices,
			U&&... accessorArgs
		)
			: BufferObject<ReaderT, WriterT, UsageSettings::STATIC, AccessSettings::WRITE>::BufferObject(
				manager,
				getIndexTypeSize(indexType) * numIndices,
				std::forward<U>(accessorArgs)...
			)
			, mIndexType(indexType)
			, mNumIndices(numIndices)
		{}

	private:
		IndexType mIndexType;
		uint mNumIndices;
	};

	TOV_NAMESPACE_END // buffers 
	TOV_NAMESPACE_END // rendering
}

#endif
