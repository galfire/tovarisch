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

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END //rendering
}

#endif
