#ifndef TOV_MEMORY_CONFIG_H
#define TOV_MEMORY_CONFIG_H

#include <tov/core.h>

#include "memory.h"

#include "memory/allocated_object.h"

#include "memory/arena/memory_arena.h"
#include "memory/arena/typed_memory_arena.h"
#include "memory/heap_area.h"

#include "memory/policies/allocation/freelist.h"
#include "memory/policies/allocation/linear.h"
#include "memory/policies/allocation/new_delete.h"

#include "memory/policies/alignment/standard.h"
#include "memory/policies/alignment/none.h"

#include "memory/policies/bounds/none.h"
#include "memory/policies/bounds/standard.h"
#include "memory/policies/bounds/token.h"

#include "memory/policies/thread/single.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    using AllocationPolicyFreelist = policies::allocation::Freelist;
    using AllocationPolicyLinear = policies::allocation::Linear;
    using AllocationPolicyNewDelete = policies::allocation::NewDelete;

    using AlignmentPolicyNone = policies::alignment::None;
    using AlignmentPolicyStandard = policies::alignment::Standard;

    using ThreadPolicySingle = policies::thread::Single;

#if TOV_DEBUG
    template <class Front, class Back>
    using Standard = policies::bounds::Standard<Front, Back>;

    template <byte TOKEN>
    using Token = policies::bounds::Token<TOKEN>;
    
    using BoundsPolicy = Standard<
        Token<0xAB>,
        Token<0xBB>
    >;
#else
    using BoundsPolicy = policies::bounds::None;
#endif

    using ArenaLinear = arena::MemoryArena<
        AllocationPolicyLinear, 
        AlignmentPolicyStandard, 
        ThreadPolicySingle, 
        BoundsPolicy
    >;

    using ArenaNewDelete = arena::MemoryArena<
        AllocationPolicyNewDelete,
        AlignmentPolicyStandard,
        ThreadPolicySingle,
        BoundsPolicy
    >;

    template <class T>
    using ArenaFreelist = arena::TypedMemoryArena<
        T,
        AllocationPolicyFreelist,
        AlignmentPolicyStandard,
        ThreadPolicySingle,
        BoundsPolicy
    >;

    TOV_NAMESPACE_END // memory
}

#endif
