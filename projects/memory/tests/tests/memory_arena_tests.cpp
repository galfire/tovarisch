#include "test_helper.h"

#include <tov/memory/memory_arena.h>
#include <tov/memory/heap_area.h>
#include <tov/memory/bounds_check_exception.h>

#include "util/policies/alignment/dummy_standard.h"
#include "util/policies/allocation/dummy_new_delete.h"
#include "util/policies/allocation/dummy_null.h"

#include "util/policies/bounds/dummy_simple.h"
#include "util/policies/bounds/dummy_false.h"

#include "util/policies/thread/dummy_unsafe.h"


TEST_CASE("MemoryArena", "[MemoryArena]")
{
    using AlignmentPolicy = tov::test::memory::policies::alignment::DummyStandard;
    using AllocationPolicy = tov::test::memory::policies::allocation::DummyNewDelete;
    using NullAllocationPolicy = tov::test::memory::policies::allocation::DummyNull;
    using BoundsPolicy = tov::test::memory::policies::bounds::DummySimple;
    using ThreadPolicy = tov::test::memory::policies::thread::DummyUnsafe;

    const size_t sz = 1024;
    tov::memory::HeapArea area(sz);

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

        SECTION("signs the allocation with the front bound signature")
        {
            tov::memory::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
            auto ptr = arena.allocate(sizeof(int), alignof(int));
            auto front = (tov::byte*)ptr - BoundsPolicy::FRONT_BOUND_SIZE;
            CHECK(memcmp(front, BoundsPolicy::FRONT_BOUND_SIGNATURE, BoundsPolicy::FRONT_BOUND_SIZE) == 0);
        }

        SECTION("signs the allocation with the end bound signature")
        {
            tov::memory::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
            auto ptr = arena.allocate(sizeof(int), alignof(int));
            auto end = (tov::byte*)ptr + sizeof(int);
            CHECK(memcmp(end, BoundsPolicy::END_BOUND_SIGNATURE, BoundsPolicy::END_BOUND_SIZE) == 0);
        }
    }

    SECTION("deallocate")
    {
        SECTION("throws an error when the front signature check fails")
        {
            using BoundsPolicy = tov::test::memory::policies::bounds::DummyFalse;
            tov::memory::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
            void* ptr = arena.allocate(64, 32);

            CHECK_THROWS_AS(arena.deallocate(ptr), tov::memory::BoundsCheckException);
        }

        SECTION("throws an error when the end signature check fails")
        {
            using BoundsPolicy = tov::test::memory::policies::bounds::DummyFalse;
            tov::memory::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
            void* ptr = arena.allocate(64, 32);

            CHECK_THROWS_AS(arena.deallocate(ptr), tov::memory::BoundsCheckException);
        }
    }
}
