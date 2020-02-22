#ifdef TOV_DEBUG
	#include <cassert>
	#include <iostream>
#endif

#include "buffer_object_manager.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class ReaderT, class WriterT, UsageSettings usageSettings>
	void BufferObject<ReaderT, WriterT, usageSettings>::read()
	{
		mBufferAccessor.read(mLockOffset, mLockLength, mScratchPointer);
	}

	template<class ReaderT, class WriterT, UsageSettings usageSettings>
	void BufferObject<ReaderT, WriterT, usageSettings>::write()
	{
		mBufferAccessor.write(mLockOffset, mLockLength, mScratchPointer);
	}

	template<class ReaderT, class WriterT, UsageSettings usageSettings>
	void BufferObject<ReaderT, WriterT, usageSettings>::discard()
	{
		//
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}
