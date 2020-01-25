#include <assert.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)

	template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::MemoryArena(const void* start, const void* end) noexcept
		: mAllocationPolicy(start, end)
		, mAlignmentPolicy()
		, mBoundsSigner()
	{
	}

	template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	inline void* MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::allocate(size_t size, size_t alignment)
	{
		mThreadPolicy.enter();

		//
		// Determine the space needed for the allocation

		/*	The required size of the user requested memory we are allocating

			The required size of the user requested memory is equal to the
			requested size plus the size of overhead.
		*/
		const size_t requiredSize = size + OVERHEAD_REQUIREMENT;

		/*	The space to store the user allocation in

			Add the alignment space to the allocation size so that there is room to
			shift the user requested memory to an aligned location.
		*/
		// The amount of space needed to accommodate alignment
		size_t alignmentSpace = mAlignmentPolicy.determineAlignmentSpace(alignment);
		size_t space = requiredSize + alignmentSpace;

		//
		// 1. Allocation Policy: Allocate the memory

		/*	Allocate the space using the allocation policy

			The amount of space actually allocated can be greater than the space
			if the allocation policy requires it.
		*/
		void* allocation = mAllocationPolicy.allocate(space);

		union
		{
			void* asRaw;
			byte* asByte;
		};
		asRaw = allocation;

		//
		// 2. Alignment Policy: Align the memory

		/*  Any data that must be written to the buffer immediately before
			the user pointer (bookkeeping, bounds checking signatures, etc.)
			will affect the alignment.

			We want to align the user requested pointer, but not the overhead
			memory that offsets it. We find the size of the offset and get a
			location (pointer) in the buffer that represents this size.
			Finally, we align this pointer, giving us the required user
			pointer.
		*/
		void* p = asByte + POLICY_OFFSET + BoundsCheckingPolicy::FRONT_BOUND_SIZE;
		asRaw = mAlignmentPolicy.align(alignment, requiredSize, p, space);

		// The final user pointer is the aligned pointer
		void* userPtr = asRaw;

		//
		// 3. Write memory headers in the space before the user pointer
		//	  [userPointer - offset, userPointer)

		asByte -= POLICY_OFFSET + BoundsCheckingPolicy::FRONT_BOUND_SIZE;

		//
		//		ORDER OF HEADERS
		//			1. Alignment Policy

		/*	Alignment Policy Header
		
			Get the difference between the aligned user pointer minus offset and the original
			allocation

			This difference tells us the distance between the location of the aligned
			pointer minus offset and the location of the originally allocated memory. When
			deallocating the memory, we must subtract this distance from the requested
			pointer we are deallocating in order to get the location of the original
			memory.

			The memory between the originally allocated memory and the aligned pointer minus offset
			is effectively wasted space. It can range from [0, alignment).
		*/
		ptrdiff_t alignmentOffset = asByte - (byte*)allocation;
		mAlignmentPolicy.writeHeader(asRaw, alignmentSpace, alignmentOffset);

		//
		// 4. Write the bounds signatures

		// Sign the front bound
		mBoundsSigner.signFront(asRaw);

		/*	Sign the end bound

			The location of the end bound is equal to the location of the start bound
			plus the allocated size, minus the overhead and alignment space.

			The allocated size will equal the space (plus any any extra memory required
			by the allocation policy). Therefore, we subtract the overhead and alignment space
			to get the requested size (with any extra policy-specific size requirements).
		*/
		size_t allocationSize = mAllocationPolicy.getAllocationSize(allocation);
		asByte += allocationSize - (OVERHEAD_REQUIREMENT + alignmentSpace);
		mBoundsSigner.signEnd(asRaw);

		mThreadPolicy.leave();

		return userPtr;
	}

	template<typename AllocationPolicy, typename AlignmentPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	inline void MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::deallocate(void* ptr)
	{
		if (!ptr)
		{
			return;
		}

		mThreadPolicy.enter();

		// Store a reference as byte to the original ptr being deallocated 
		byte* ptrAsByte = (byte*)ptr;


		//
		//		ORDER OF HEADERS
		//			1. AlignmentPolicy

		byte* headersLocation = (byte*)ptr - (POLICY_OFFSET + BoundsCheckingPolicy::FRONT_BOUND_SIZE);
		
		void* currentLocation = (void*)headersLocation;

		size_t alignmentSpace;
		ptrdiff_t alignmentOffset;
		mAlignmentPolicy.readHeader(currentLocation, alignmentSpace, alignmentOffset);

		void* allocationPtr = headersLocation - alignmentOffset;

		// Check guards
		void* frontGuard = currentLocation;
		assert(mBoundsCheckingPolicy.checkFrontSignature(frontGuard));

		size_t allocationSize = mAllocationPolicy.getAllocationSize(allocationPtr);
		byte* endGuard = ptrAsByte + allocationSize - (OVERHEAD_REQUIREMENT + alignmentSpace);
		assert(mBoundsCheckingPolicy.checkEndSignature(endGuard));

		// Deallocate

		mAllocationPolicy.deallocate(allocationPtr);

		mThreadPolicy.leave();
	}

	template<typename AllocationPolicy, typename AlignmentPolicy,typename ThreadPolicy, typename BoundsCheckingPolicy>
	inline void MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsCheckingPolicy>::reset()
	{
		mAllocationPolicy.reset();
	}

	TOV_NAMESPACE_END // memory
}