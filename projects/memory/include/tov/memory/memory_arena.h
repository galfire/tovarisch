#ifndef TOV_MEMORY_MEMORY_ARENA_H
#define TOV_MEMORY_MEMORY_ARENA_H

#include <tov/core.h>

#include "bounds_signer.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    struct AllocationHeader
    {
        void* originalPtr;
        size_t allocationSize;
    };

    template<
        typename AllocationPolicy,
        typename AlignmentPolicy,
        typename ThreadPolicy,
        typename BoundsCheckingPolicy
    >
    class MemoryArena
    {
        TOV_MOVABLE_ONLY(MemoryArena)

    public:
        inline explicit MemoryArena() = default;
        inline explicit MemoryArena(const void* start, const void* end) noexcept;
        inline ~MemoryArena() noexcept = default;

        inline void* allocate(size_t size, size_t alignment);
        inline void deallocate(void* ptr);
        inline void reset();

        inline void checkBounds(void* ptr) const;

    private:
        inline auto getAllocationHeader(void* ptr) const -> AllocationHeader
        {
            auto cursor = static_cast<byte*>(ptr);
            cursor -= BoundsCheckingPolicy::FRONT_BOUND_SIZE;
            cursor -= sizeof(AllocationHeader);
            return *reinterpret_cast<AllocationHeader*>(cursor);
        }

    private:
        AllocationPolicy mAllocationPolicy;
        AlignmentPolicy mAlignmentPolicy;
        ThreadPolicy mThreadPolicy;
        BoundsCheckingPolicy mBoundsCheckingPolicy;
        BoundsSigner<BoundsCheckingPolicy> mBoundsSigner;
    };

    template <typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
    using MemoryArenaUPtr = std::unique_ptr<MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>>;

    TOV_NAMESPACE_END // memory
}

#include "memory_arena.inl"

#endif 
