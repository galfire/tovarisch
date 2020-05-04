#ifndef TOV_RENDERING_BUFFERS_GUARD_H
#define TOV_RENDERING_BUFFERS_GUARD_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class BufferT>
	class Guard
	{
	public:
		template<class... U>
		Guard(BufferT& buffer, U&&... args)
			: mBuffer(buffer)
		{
			mLock = mBuffer.lock(std::forward<U>(args)...);
		}

		~Guard()
		{
			mBuffer.unlock();
		}

		auto getLock() const { return mLock; }

	private:
		BufferT& mBuffer;
		void* mLock = nullptr;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif