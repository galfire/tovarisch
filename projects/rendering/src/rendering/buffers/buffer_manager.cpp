#include "rendering/buffers/buffer_manager.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	BufferManager::BufferManager() noexcept
		: mMemoryArena()
	{}

	void* BufferManager::allocateScratch(size_t size)
	{
		return mMemoryArena.allocate(size, 32);
	}

	void BufferManager::deallocateScratch(void* ptr)
	{
		return mMemoryArena.deallocate(ptr);
	}

	void BufferManager::checkBounds(void* ptr) const
	{
		mMemoryArena.checkBounds(ptr);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}