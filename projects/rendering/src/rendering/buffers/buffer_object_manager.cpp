#include "rendering/buffers/buffer_object_manager.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	BufferObjectManager::BufferObjectManager() noexcept
		: mMemoryArena()
	{}

	void* BufferObjectManager::allocateScratch(size_t size)
	{
		return mMemoryArena.allocate(size, 32);
	}

	void BufferObjectManager::deallocateScratch(void* ptr)
	{
		return mMemoryArena.deallocate(ptr);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}