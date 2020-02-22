#include "buffer_object_manager.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class ReaderT, class WriterT, UsageSettings usageSettings, AccessSettings accessSettings>
	void BufferObject<ReaderT, WriterT, usageSettings, accessSettings>::read()
	{
		mBufferAccessor.read(mLockOffset, mLockLength, mScratchPointer);
	}

	template<class ReaderT, class WriterT, UsageSettings usageSettings, AccessSettings accessSettings>
	void BufferObject<ReaderT, WriterT, usageSettings, accessSettings>::write()
	{
		mBufferAccessor.write(mLockOffset, mLockLength, mScratchPointer);
	}

	template<class ReaderT, class WriterT, UsageSettings usageSettings, AccessSettings accessSettings>
	void BufferObject<ReaderT, WriterT, usageSettings, accessSettings>::discard()
	{
		//
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}
