#include "test_helper.h"

#include <tov/memory/memory_arena.h>
#include <tov/memory/policies/alignment/standard.h>
#include <tov/memory/policies/bounds/simple.h>
#include "util/dummy_allocation_policy.h"
#include "util/dummy_null_allocation_policy.h"
#include "util/dummy_thread_policy.h"

TEST_CASE("MemoryArena", "[MemoryArena]")
{
    using AllocationPolicy = tov::test::memory::DummyAllocationPolicy;
    using NullAllocationPolicy = tov::test::memory::DummyNullAllocationPolicy;
    using AlignmentPolicy = tov::memory::policies::alignment::Standard;
    using BoundsPolicy = tov::memory::policies::bounds::Simple;
    using ThreadPolicy = tov::test::memory::DummyThreadPolicy;

    SECTION("allocate")
    {
        SECTION("returns a valid pointer")
        {
            tov::memory::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;

            void* ptr = arena.allocate(64, 32);
            CHECK(ptr != nullptr);
        }

        SECTION("allocates a block of memory suitable for the specified size")
        {
            tov::memory::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;

            void* ptr = arena.allocate(sizeof(int), alignof(int));
            int* value = static_cast<int*>(ptr);
            *value = 42;
            CHECK(*value == 42);
        }

        SECTION("allocates a block of memory aligned to the specified alignment")
        {
            tov::memory::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;

            void* ptr = arena.allocate(sizeof(int), alignof(int));
            CHECK((uintptr_t)ptr % alignof(int) == 0);
        }

        SECTION("throws a bad_alloc when the allocation policy returns null")
        {
            tov::memory::MemoryArena<NullAllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;

            CHECK_THROWS_AS(arena.allocate(8, 8), std::bad_alloc);
        }
    }

    SECTION("deallocate")
    {
        tov::memory::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
        void* ptr = arena.allocate(64, 32);

        SECTION("does something")
        {
            arena.deallocate(ptr);
        }
    }
}
