#ifndef TOV_RENDERING_BUFFERS_BUFFER_H
#define TOV_RENDERING_BUFFERS_BUFFER_H

#include <tov/rendering/rendering_core.h>

#include "access_settings.h"
#include "buffer_accessor.h"
#include "lock_settings.h"
#include "usage_settings.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	class BufferManagerBase;

	class BufferBase
	{
		TOV_MOVABLE_ONLY(BufferBase)

		friend class BufferManagerBase;

	public:
		virtual ~BufferBase() = default;

		// Lock a part of the buffer [offset, offset + length)
		auto lock(size_t offset, size_t length, LockSettings lockSettings) -> void*;
		
		// Lock the whole buffer
		auto lock(LockSettings lockSettings) -> void*;

		void unlock();

	protected:
		BufferBase(
			BufferManagerBase& manager,
			size_t bytes
		)
			: mManager(manager)
			, mBytes(bytes)
			, mCurrentBuffer(mBuffer)
			, mCurrentScratch(mScratch)
		{}

		// Connect this instance to the external buffer
		virtual void map() TOV_ABSTRACT;
		virtual void unmap() TOV_ABSTRACT;

		// Commit the data in scratch memory to the buffer 
		virtual void write() TOV_ABSTRACT;

		// Read the buffer data into scratch memory
		virtual void read() TOV_ABSTRACT;

		// Discard the data in the buffer
		virtual void discard() {}
			
	protected:
		BufferManagerBase& mManager;

		// The external buffer store
		void* mBuffer = nullptr;
		void*& mCurrentBuffer;

		// Scratch pointer
		void* mScratch = nullptr;
		void*& mCurrentScratch;

		// Size of the buffer store
		size_t mBytes;
		// Where in the buffer the lock starts
		size_t mLockOffset = 0;
		// The length of the locked portion of the buffer
		size_t mLockLength = 0;
		// The lock settings
		LockSettings mLockSettings = static_cast<LockSettings>(0);

	private:
		bool mLocked = false;
	};

	using BufferUPtr = std::unique_ptr<BufferBase>;

	template<
		class ReaderT,
		class WriterT,
		UsageSettings usageSettings,
		AccessSettings accessSettings
	>
	class Buffer
		: public BufferBase
	{
	public:
		template<class... U>
		Buffer(
			BufferManagerBase& manager,
			size_t bytes,
			U&&... accessorArgs
		)
			: BufferBase(manager, bytes)
			, mBufferAccessor(
				mCurrentBuffer,
				mCurrentScratch,
				std::forward<U>(accessorArgs)...
			)
		{}

	private:
		void read() override;
		void write() override;

	private:
		BufferAccessor<ReaderT, WriterT, accessSettings> mBufferAccessor;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#include "buffer.inl"

#endif // !TOV_RENDERING_BUFFER_H
