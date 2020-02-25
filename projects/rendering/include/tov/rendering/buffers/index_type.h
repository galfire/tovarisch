#ifndef TOV_RENDERING_BUFFERS_INDEX_TYPE_H
#define TOV_RENDERING_BUFFERS_INDEX_TYPE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	enum class IndexType
	{
		BITS_8,
		BITS_16,
		BITS_32,
	};

	constexpr IndexType getIndexType(uint numIndices)
	{
		IndexType                        indexType = IndexType::BITS_32;
		if      (numIndices < (1 << 8))  indexType = IndexType::BITS_8;
		else if (numIndices < (1 << 16)) indexType = IndexType::BITS_16;
		else                             indexType = IndexType::BITS_32;
		return indexType;
	}

	constexpr size_t getIndexTypeSize(IndexType indexType)
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

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END //rendering
}

#endif