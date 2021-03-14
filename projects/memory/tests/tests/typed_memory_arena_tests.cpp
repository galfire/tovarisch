#include "test_helper.h"

#include <tov/memory/memory_arena.h>
#include <tov/memory/policies/alignment/standard.h>
#include <tov/memory/policies/bounds/simple.h>

#include "util/policies/allocation/dummy_fixed.h"
#include "util/policies/allocation/dummy_null.h"
#include "util/policies/alignment/dummy_standard.h"
#include "util/policies/thread/dummy_unsafe.h"

#include <tov/memory/heap_area.h>

TEST_CASE("TypedMemoryArena", "[MemoryArena]")
{
    using AllocationPolicy = tov::test::memory::policies::allocation::DummyFixed;
    using NullAllocationPolicy = tov::test::memory::policies::allocation::DummyNull;
    using AlignmentPolicy = tov::test::memory::policies::alignment::DummyStandard;
    using ThreadPolicy = tov::test::memory::policies::thread::DummyUnsafe;

    using BoundsPolicy = tov::memory::policies::bounds::Simple;

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
