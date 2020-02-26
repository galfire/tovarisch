#ifndef TOV_MEMORY_MEMORY_ARENA_H
#define TOV_MEMORY_MEMORY_ARENA_H

#include <tov/core.h>

#include "bounds_signer.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)

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
		AllocationPolicy mAllocationPolicy;
		AlignmentPolicy mAlignmentPolicy;
		ThreadPolicy mThreadPolicy;
		BoundsCheckingPolicy mBoundsCheckingPolicy;
		BoundsSigner<BoundsCheckingPolicy> mBoundsSigner;

	public:
		// Size of the offset created by all policy headers
		constexpr static size_t POLICY_OFFSET =
			AlignmentPolicy::POLICY_OFFSET;

		constexpr static size_t OVERHEAD_REQUIREMENT = 
			POLICY_OFFSET +
			BoundsCheckingPolicy::TOTAL_BOUND_SIZE;
	};

	template <typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	using MemoryArenaUPtr = std::unique_ptr<MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>>;

	TOV_NAMESPACE_END // memory
}

#include "memory_arena.inl"

#endif 