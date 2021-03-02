#include <cstring> // std::memcpy
#include <new>

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)
	TOV_NAMESPACE_BEGIN(policies)
	TOV_NAMESPACE_BEGIN(alignment)

	inline size_t Standard::determineAlignmentSpace(size_t alignment) noexcept
	{
		return alignment;
	}

	inline void* Standard::align(size_t alignment, size_t size, void*& ptr, size_t& space) noexcept
	{
		// Can we shift the requested memory block forward to an aligned address within the allocated space?
		//assert(std::align(alignment, size, ptr, space));
		// The test pointer can successfully be aligned; align the user pointer now
		void* alignedPtr = std::align(alignment, size, ptr, space);
		//assert((uintptr_t)ptr % alignment == 0);
		return alignedPtr;
	}

	inline void Standard::writeHeader(void*& ptr, size_t alignmentSpace, ptrdiff_t alignmentOffset) const noexcept
	{
		auto header = BlockHeader { alignmentSpace, alignmentOffset };
		accessor.write(ptr, &header);

		union
		{
			void** raw;
			tov::byte** byte;
		};

		raw = &ptr;
		*byte += sizeof(BlockHeader);
	}

	inline void Standard::readHeader(void*& ptr, size_t& alignmentSpace, ptrdiff_t& alignmentOffset) const noexcept
	{
		auto header = BlockHeader {};
		accessor.read(ptr, header);
		alignmentSpace = header.alignmentSpace;
		alignmentOffset = header.alignmentOffset;

		union
		{
			void** raw;
			tov::byte** byte;
		};

		raw = &ptr;
		*byte += sizeof(BlockHeader);
	}

	TOV_NAMESPACE_END // allocation
	TOV_NAMESPACE_END // policies
	TOV_NAMESPACE_END // memory
}