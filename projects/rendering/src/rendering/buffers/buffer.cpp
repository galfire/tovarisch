#include "rendering/buffers/buffer.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	auto BufferBase::lock(size_t offset, size_t length, LockSettings lockSettings) -> void*
	{
		assert(!mLocked && "Buffer is already locked!");

		if (!mBuffer)
		{
			map();
		}

		if (length + offset > mBytes)
		{
			assert(false && "Lock out of bounds!");
		}

		mLocked = true;
		mLockOffset = offset;
		mLockLength = length;
		mLockSettings = lockSettings;
		mScratch = mManager.allocateScratch(mBytes);

		if ((mLockSettings & LockSettings::DISCARD) == LockSettings::DISCARD)
		{
			discard();
		}

		if ((mLockSettings & LockSettings::READ) == LockSettings::READ)
		{
			read();
		}

		return mScratch;
	}

	auto BufferBase::lock(LockSettings lockSettings) -> void*
	{
		auto buffer = lock(0, mBytes, lockSettings);
		return buffer;
	}

	void BufferBase::unlock()
	{
		assert(mLocked && "Buffer is not locked!");

		if (mScratch)
		{
			if ((mLockSettings & LockSettings::WRITE) == LockSettings::WRITE)
			{
				mManager.checkBounds(mScratch);
				write();
			}

			mManager.deallocateScratch(mScratch);
		}

		mLocked = false;
		mLockOffset = 0;
		mLockLength = 0;
		mLockSettings = static_cast<LockSettings>(0);
		mScratch = nullptr;
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}
