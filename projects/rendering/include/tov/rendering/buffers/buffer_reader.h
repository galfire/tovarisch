#ifndef TOV_RENDERING_BUFFERS_BUFFER_READER_H
#define TOV_RENDERING_BUFFERS_BUFFER_READER_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class ReaderT>
	class BufferReader
	{
	public:
		void read(size_t offset, size_t length, void* pDest)
		{
			static_cast<ReaderT*>(this)->readImpl(offset, length, pDest);
		}
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif
