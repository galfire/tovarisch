#ifndef TOV_RENDERING_BUFFERS_BUFFER_OBJECT_H
#define TOV_RENDERING_BUFFERS_BUFFER_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "buffer_accessor.h"
#include "lock_settings.h"
#include "usage_settings.h"

#include <iostream>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	class BufferObjectManager;

	class BufferObjectBase
	{
		TOV_MOVABLE_ONLY(BufferObjectBase)

		friend class BufferObjectManager;

	public:
		virtual ~BufferObjectBase() = default;

		// Lock a part of the buffer [offset, offset + length)
		void* lock(size_t offset, size_t length, LockSettings lockSettings);
		
		// Lock the whole buffer
		void* lock(LockSettings lockSettings);

		void unlock();

	protected:
		BufferObjectBase(
			BufferObjectManager& manager,
			size_t bytes
		);

		// Commit the data in scratch memory to the buffer 
		virtual void write() TOV_ABSTRACT;

		// Read the buffer data into scratch memory
		virtual void read() TOV_ABSTRACT;

		// Discard the data in the buffer
		virtual void discard() TOV_ABSTRACT;
			
	protected:
		BufferObjectManager& mManager;

		// Size of the buffer
		size_t mBytes;

		// Scratch pointer
		void* mScratchPointer = nullptr;

		// Where in the buffer the lock starts
		size_t mLockOffset = 0;
		// The length of the locked portion of the buffer
		size_t mLockLength = 0;
		// The lock settings
		LockSettings mLockSettings = static_cast<LockSettings>(0);

	private:
		bool mLocked = false;
	};

	using BufferObjectUPtr = std::unique_ptr<BufferObjectBase>;

	template<class ReaderT, class WriterT, UsageSettings usageSettings>
	class BufferObject
		: public BufferObjectBase
	{
		using Reader = ReaderT;
		using Writer = WriterT;

	public:
		template<class... U>
		BufferObject(
			BufferObjectManager& manager,
			size_t bytes,
			U&&... accessorArgs
		) 
			: BufferObjectBase(manager, bytes)
			, mBufferAccessor(std::forward<U>(accessorArgs)...)
		{}

	private:
		void read() override;
		void write() override;
		void discard() override;

	private:
		BufferAccessor<Reader, Writer, usageSettings> mBufferAccessor;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#include "buffer_object.inl"

#endif // !TOV_RENDERING_BUFFER_OBJECT_H
