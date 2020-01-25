#ifndef TOV_MEMORY_CONFIG_H
#define TOV_MEMORY_CONFIG_H

#include <tov/core.h>

#include "memory.h"

#include "memory/allocated_object.h"

#include "memory/memory_arena.h"
#include "memory/heap_area.h"

#include "memory/policies/allocation/linear.h"

#include "memory/policies/alignment/standard.h"
#include "memory/policies/alignment/none.h"

#include "memory/policies/bounds/none.h"
#include "memory/policies/bounds/simple.h"

#include "memory/policies/thread/single.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)

	using AllocationPolicyLinear = policies::allocation::Linear;

	using AlignmentPolicyStandard = policies::alignment::Standard;
	//using AlignmentPolicyStandard = policies::alignment::None;

	using ThreadPolicySingle = policies::thread::Single;

#if TOV_DEBUG
	using BoundsPolicy = policies::bounds::Simple;
#else
	using BoundsPolicy = policies::bounds::None;
#endif

	template<size_t Index>
	class IndexedHeapArea
	{
	public:
		enum
		{
			INDEX = Index
		};

	public:
		IndexedHeapArea(size_t sz)
		{
			mHeapArea = std::make_unique<HeapArea>(sz);
		}

		inline void* getStart(void) const { return mHeapArea->getStart(); }
		inline void* getEnd(void) const { return mHeapArea->getEnd(); }

	private:
		HeapAreaUPtr mHeapArea;
	};

	using ArenaLinear = MemoryArena<
		AllocationPolicyLinear, 
		AlignmentPolicyStandard, 
		ThreadPolicySingle, 
		BoundsPolicy
	>;

	using AllocatedObjectLinear = AllocatedObject<ArenaLinear, IndexedHeapArea<0>, 4_mb>;

	TOV_NAMESPACE_END // memory
}

#endif