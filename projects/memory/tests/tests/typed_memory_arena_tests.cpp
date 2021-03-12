#include "test_helper.h"

#include <tov/memory/memory_arena.h>
#include <tov/memory/policies/alignment/standard.h>
#include <tov/memory/policies/bounds/simple.h>

#include "util/dummy_fixed_allocation_policy.h"
#include "util/dummy_null_allocation_policy.h"
#include "util/dummy_thread_policy.h"

#include <tov/memory/heap_area.h>

TEST_CASE("TypedMemoryArena", "[MemoryArena]")
{
    using AllocationPolicy = tov::test::memory::DummyFixedAllocationPolicy;
    using NullAllocationPolicy = tov::test::memory::DummyNullAllocationPolicy;
    using AlignmentPolicy = tov::memory::policies::alignment::Standard;
    using BoundsPolicy = tov::memory::policies::bounds::Simple;
    using ThreadPolicy = tov::test::memory::DummyThreadPolicy;

    const auto sz = 1024;
    tov::memory::HeapArea area(sz);
    const auto start = area.getStart();
    const auto end = area.getEnd();

    SECTION("allocate")
    {
        SECTION("returns a valid pointer")
        {
            tov::memory::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);

            void* ptr = arena.allocate();
            CHECK(ptr != nullptr);
            CHECK(ptr >= start);
            CHECK(ptr < end);
        }

        SECTION("allocates a block of memory suitable for the specified size")
        {
            tov::memory::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);

            void* ptr = arena.allocate();
            int* value = static_cast<int*>(ptr);
            *value = 42;
            CHECK(*value == 42);
        }

        SECTION("allocates a block of memory aligned to the specified alignment")
        {
            tov::memory::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);

            void* ptr = arena.allocate();
            CHECK((uintptr_t)ptr % alignof(int) == 0);
        }

        SECTION("throws a bad_alloc when the allocation policy returns null")
        {
            tov::memory::TypedMemoryArena<int, NullAllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);

            CHECK_THROWS_AS(arena.allocate(), std::bad_alloc);
        }
    }

    SECTION("deallocate")
    {
        tov::memory::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);
        void* ptr = arena.allocate();

        SECTION("does something")
        {
            arena.deallocate(ptr);
        }
    }
}
