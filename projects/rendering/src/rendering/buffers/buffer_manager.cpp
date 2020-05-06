#include "rendering/buffers/buffer_manager.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    BufferManagerBase::BufferManagerBase() noexcept
        : mMemoryArena()
    {}

    auto BufferManagerBase::allocateScratch(size_t size) -> void*
    {
        return mMemoryArena.allocate(size, 32);
    }

    void BufferManagerBase::deallocateScratch(void* ptr)
    {
        return mMemoryArena.deallocate(ptr);
    }

    void BufferManagerBase::checkBounds(void* ptr) const
    {
        mMemoryArena.checkBounds(ptr);
    }

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}
