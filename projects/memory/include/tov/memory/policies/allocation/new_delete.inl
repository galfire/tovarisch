#include <cstring> // std::memcpy
#include <new>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(allocation)

    inline void* NewDelete::allocate(size_t size)
    {
        union
        {
            void* asRaw;
            byte* asByte;
        };

        // Prefix the memory with a header to store metadata
        // Adjust the allocation size to fit a header
        size_t requiredSize = size + sizeof(BlockHeader);
        asRaw = ::operator new(requiredSize);
        void* originalAllocation = asRaw;

        BlockHeader header;
        header.mAllocationSize = size;
        // Append the header
        memcpy(asRaw, &header, sizeof(BlockHeader));

        // Return the memory after the header
        asByte += sizeof(BlockHeader);

        return asRaw;
    }

    inline void NewDelete::deallocate(void* ptr) noexcept
    {
        union
        {
            void* asRaw;
            BlockHeader* asHeader;
        };

        // Include the block header in the delete call so we can delete it too
        asRaw = ptr;
        asHeader = &asHeader[-1];

        ::operator delete(asRaw);
    }

    inline void NewDelete::reset() noexcept
    {
        // Nothing
    }

    inline size_t NewDelete::getAllocationSize(void* ptr) const noexcept
    {
        union
        {
            void* asRaw;
            BlockHeader* asHeader;
        };

        asRaw = ptr;
        size_t userDataSize = asHeader[-1].mAllocationSize;
        return userDataSize;
    }

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}
