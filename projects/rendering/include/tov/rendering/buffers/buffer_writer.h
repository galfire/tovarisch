#ifndef TOV_RENDERING_BUFFERS_BUFFER_WRITER_H
#define TOV_RENDERING_BUFFERS_BUFFER_WRITER_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class WriterT>
	class BufferWriter
	{
	public:
		void write(size_t offset, size_t length, void* pSrc)
		{
			static_cast<WriterT*>(this)->writeImpl(offset, length, pSrc);
		}
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif
