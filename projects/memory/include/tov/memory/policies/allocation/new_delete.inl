#include <new>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(allocation)

    inline void* NewDelete::allocate(size_t size) noexcept
    {
        return ::operator new(size, std::nothrow);
    }

    inline void NewDelete::deallocate(void* ptr) noexcept
    {
        ::operator delete(ptr);
    }

    inline void NewDelete::reset() noexcept
    {
        // Nothing
    }

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}
