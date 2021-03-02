#include "test_helper.h"

#include <tov/memory/memory_arena.h>
#include <tov/memory/policies/alignment/standard.h>
#include "util/dummy_allocation_policy.h"
#include <tov/memory/policies/bounds/simple.h>

class DummyThreadPolicy
{
public:
    void enter() {};
    void leave() {};
};

TEST_CASE("MemoryArena", "[MemoryArena]")
{
    using DummyAllocationPolicy = tov::test::memory::DummyAllocationPolicy;
    using AlignmentPolicy = tov::memory::policies::alignment::Standard;
    using DummyBoundsPolicy = tov::memory::policies::bounds::Simple;

    tov::memory::MemoryArena<DummyAllocationPolicy, AlignmentPolicy, DummyThreadPolicy, DummyBoundsPolicy> arena;

    SECTION("allocate")
    {
        SECTION("returns a valid pointer")
        {
            void* ptr = arena.allocate(64, 32);
            CHECK(ptr != nullptr);
        }

        SECTION("allocates a block of memory suitable for the specified size")
        {
            void* ptr = arena.allocate(sizeof(int), alignof(int));
            int* value = static_cast<int*>(ptr);
            *value = 42;
            CHECK(*value == 42);
        }

        SECTION("allocates a block of memory aligned to the specified alignment")
        {
            void* ptr = arena.allocate(sizeof(int), alignof(int));
            CHECK((uintptr_t)ptr % alignof(int) == 0);
        }
    }

    SECTION("deallocate")
    {
        void* ptr = arena.allocate(64, 32);

        SECTION("does something")
        {
            arena.deallocate(ptr);
        }
    }
}