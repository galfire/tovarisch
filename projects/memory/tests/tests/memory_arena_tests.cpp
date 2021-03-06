#include "test_helper.h"

#include <tov/memory/arena/memory_arena.h>

#include <tov/memory/heap_area.h>
#include <tov/memory/bounds_check_exception.h>

#include "util/policies/alignment/dummy_standard.h"

#include "util/policies/allocation/dummy_new_delete.h"
#include "util/policies/allocation/dummy_null.h"

#include "util/policies/bounds/dummy_standard.h"
#include "util/policies/bounds/dummy_token.h"
#include "util/policies/bounds/dummy_token_true.h"
#include "util/policies/bounds/dummy_token_false.h"

#include "util/policies/thread/dummy_unsafe.h"

namespace
{
    template <class F, class B>
    using StandardBoundsPolicy = tov::test::memory::policies::bounds::DummyStandard<F, B>;

    template <unsigned char TOKEN>
    using Token = tov::test::memory::policies::bounds::DummyToken<TOKEN>;

    using TokenTrue = tov::test::memory::policies::bounds::DummyTokenTrue;
    using TokenFalse = tov::test::memory::policies::bounds::DummyTokenFalse;
    using BoundsPolicy = StandardBoundsPolicy<TokenTrue, TokenTrue>;

    using AlignmentPolicy = tov::test::memory::policies::alignment::DummyStandard;
    
    using AllocationPolicy = tov::test::memory::policies::allocation::DummyNewDelete;
    using NullAllocationPolicy = tov::test::memory::policies::allocation::DummyNull;

    using ThreadPolicy = tov::test::memory::policies::thread::DummyUnsafe;
}

TEST_CASE("MemoryArena", "[MemoryArena]")
{
    const size_t sz = 1024;
    tov::memory::HeapArea area(sz);

    SECTION("allocate")
    {
        SECTION("returns a valid pointer")
        {
            tov::memory::arena::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;

            void* ptr = arena.allocate(64, 32);
            CHECK(ptr != nullptr);
        }

        SECTION("allocates a block of memory suitable for the specified size")
        {
            tov::memory::arena::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;

            void* ptr = arena.allocate(sizeof(int), alignof(int));
            int* value = static_cast<int*>(ptr);
            *value = 42;
            CHECK(*value == 42);
        }

        SECTION("allocates a block of memory aligned to the specified alignment")
        {
            tov::memory::arena::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;

            void* ptr = arena.allocate(sizeof(int), alignof(int));
            CHECK((uintptr_t)ptr % alignof(int) == 0);
        }

        SECTION("throws a bad_alloc when the allocation policy returns null")
        {
            tov::memory::arena::MemoryArena<NullAllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;

            CHECK_THROWS_AS(arena.allocate(8, 8), std::bad_alloc);
        }

        SECTION("signs the allocation with the front bound signature")
        {
            using BoundsPolicy = StandardBoundsPolicy<Token<'a'>, Token<'z'>>;
            tov::memory::arena::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
            auto ptr = arena.allocate(sizeof(int), alignof(int));
            auto front = (tov::byte*)ptr - BoundsPolicy::FRONT_BOUND_SIZE;
            
            constexpr auto expectedSignature = "aaaa";
            CHECK(memcmp(front, expectedSignature, 4) == 0);
        }

        SECTION("signs the allocation with the end bound signature")
        {
            using BoundsPolicy = StandardBoundsPolicy<Token<'a'>, Token<'z'>>;
            tov::memory::arena::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
            auto ptr = arena.allocate(sizeof(int), alignof(int));
            auto end = (tov::byte*)ptr + sizeof(int);

            constexpr auto expectedSignature = "zzzz";
            CHECK(memcmp(end, expectedSignature, 4) == 0);
        }
    }

    SECTION("deallocate")
    {
        SECTION("throws an error when the front signature check fails")
        {
            using BoundsPolicy = StandardBoundsPolicy<TokenFalse, TokenFalse>;
            tov::memory::arena::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
            void* ptr = arena.allocate(64, 32);

            CHECK_THROWS_AS(arena.deallocate(ptr), tov::memory::BoundsCheckException);
        }

        SECTION("throws an error when the end signature check fails")
        {
            using BoundsPolicy = StandardBoundsPolicy<TokenTrue, TokenFalse>;
            tov::memory::arena::MemoryArena<AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena;
            void* ptr = arena.allocate(64, 32);

            CHECK_THROWS_AS(arena.deallocate(ptr), tov::memory::BoundsCheckException);
        }
    }
}
