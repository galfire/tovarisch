#include "rendering/buffers/buffer_object.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	BufferObjectBase::BufferObjectBase(
		BufferObjectManager& manager,
		size_t bytes
	)
		: mManager(manager)
		, mBytes(bytes)
	{}

	void* BufferObjectBase::lock(size_t offset, size_t length, LockSettings lockSettings)
	{
		assert(!mLocked && "Buffer is already locked!");

		if (length + offset > mBytes)
		{
			assert(false && "Lock out of bounds!");
		}

		mLocked = true;
		mLockOffset = offset;
		mLockLength = length;
		mLockSettings = lockSettings;

		mScratchPointer = mManager.allocateScratch(mBytes);

		if ((mLockSettings & LockSettings::DISCARD) != 0)
		{
			discard();
		}

		if ((mLockSettings & LockSettings::READ) != 0)
		{
			read();
		}

		return mScratchPointer;
	}

	void* BufferObjectBase::lock(LockSettings lockSettings)
	{
		void* buffer = lock(0, mBytes, lockSettings);
		return buffer;
	}

	void BufferObjectBase::unlock()
	{
		assert(mLocked && "Buffer is not locked!");

		if (
			mScratchPointer &&
			(mLockSettings & LockSettings::WRITE) != 0
			)
		{
			write();
		}

		if (mScratchPointer)
		{
			mManager.deallocateScratch(mScratchPointer);
		}

		mLocked = false;
		mLockOffset = 0;
		mLockLength = 0;
		mLockSettings = static_cast<LockSettings>(0);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}
