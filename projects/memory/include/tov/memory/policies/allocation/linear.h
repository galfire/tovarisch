#ifndef TOV_MEMORY_POLICIES_ALLOCATION_LINEAR_H
#define TOV_MEMORY_POLICIES_ALLOCATION_LINEAR_H

#include <tov/core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)
	TOV_NAMESPACE_BEGIN(policies)
	TOV_NAMESPACE_BEGIN(allocation)

	class Linear
	{
	private:
		struct BlockHeader
		{
			size_t mAllocationSize;
		};

	public:
		template<typename U>
		struct rebind
		{
			typedef Linear other;
		};

	public:
		inline explicit Linear(const void* start, const void* end) noexcept;
		inline ~Linear() noexcept = default;

		inline void* allocate(size_t size);
		inline void deallocate(void* ptr) noexcept;
		inline void reset() noexcept;

		inline size_t getAllocationSize(void* ptr) const noexcept;

	private:
		const void* mStart = nullptr;
		const void* mEnd = nullptr;
		void* mCurrent = nullptr;

	public:
		constexpr static bool STL_ALLOCATOR_COMPATIBLE = true;
		constexpr static bool ALLOCATED_OBJECT_COMPATIBLE = true;
	};

	TOV_NAMESPACE_END // allocation
	TOV_NAMESPACE_END // policies
	TOV_NAMESPACE_END // memory
}

#include "linear.inl"

#endif