#ifndef TOV_MEMORY_CONFIG_H
#define TOV_MEMORY_CONFIG_H

#include <tov/core.h>

#include "memory.h"

#include "memory/allocated_object.h"

#include "memory/memory_arena.h"
#include "memory/heap_area.h"

#include "memory/policies/allocation/linear.h"
#include "memory/policies/allocation/new_delete.h"

#include "memory/policies/alignment/standard.h"
#include "memory/policies/alignment/none.h"

#include "memory/policies/bounds/none.h"
#include "memory/policies/bounds/simple.h"

#include "memory/policies/thread/single.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)

	using AllocationPolicyLinear = policies::allocation::Linear;
	using AllocationPolicyNewDelete = policies::allocation::NewDelete;

	using AlignmentPolicyNone = policies::alignment::None;
	using AlignmentPolicyStandard = policies::alignment::Standard;

	using ThreadPolicySingle = policies::thread::Single;

#if TOV_DEBUG
	using BoundsPolicy = policies::bounds::Simple;
#else
	using BoundsPolicy = policies::bounds::None;
#endif

	using ArenaLinear = MemoryArena<
		AllocationPolicyLinear, 
		AlignmentPolicyStandard, 
		ThreadPolicySingle, 
		BoundsPolicy
	>;

	using ArenaNewDelete = MemoryArena<
		AllocationPolicyNewDelete,
		AlignmentPolicyStandard,
		ThreadPolicySingle,
		BoundsPolicy
	>;

	TOV_NAMESPACE_END // memory
}

#endif