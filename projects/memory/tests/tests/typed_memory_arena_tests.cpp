#include "test_helper.h"

#include <tov/memory/arena/typed_memory_arena.h>

#include <tov/memory/heap_area.h>
#include <tov/memory/bounds_check_exception.h>

#include "util/policies/allocation/dummy_fixed.h"
#include "util/policies/allocation/dummy_null.h"

#include "util/policies/alignment/dummy_standard.h"

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

    using AllocationPolicy = tov::test::memory::policies::allocation::DummyFixed;
    using NullAllocationPolicy = tov::test::memory::policies::allocation::DummyNull;

    using ThreadPolicy = tov::test::memory::policies::thread::DummyUnsafe;
}

TEST_CASE("TypedMemoryArena", "[MemoryArena]")
{
    const auto sz = 1024;
    tov::memory::HeapArea area(sz);
    const auto start = area.getStart();
    const auto end = area.getEnd();

    SECTION("allocate")
    {
        SECTION("returns a valid pointer")
        {
            tov::memory::arena::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);

            void* ptr = arena.allocate();
            CHECK(ptr != nullptr);
            CHECK(ptr >= start);
            CHECK(ptr < end);
        }

        SECTION("allocates a block of memory suitable for the specified size")
        {
            tov::memory::arena::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);

            void* ptr = arena.allocate();
            int* value = static_cast<int*>(ptr);
            *value = 42;
            CHECK(*value == 42);
        }

        SECTION("allocates a block of memory aligned to the specified alignment")
        {
            tov::memory::arena::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);

            void* ptr = arena.allocate();
            CHECK((uintptr_t)ptr % alignof(int) == 0);
        }

        SECTION("throws a bad_alloc when the allocation policy returns null")
        {
            tov::memory::arena::TypedMemoryArena<int, NullAllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);

            CHECK_THROWS_AS(arena.allocate(), std::bad_alloc);
        }

        SECTION("signs the allocation with the front bound signature")
        {
            using BoundsPolicy = StandardBoundsPolicy<Token<'a'>, Token<'z'>>;
            tov::memory::arena::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);
            auto ptr = arena.allocate();
            auto front = (tov::byte*)ptr - BoundsPolicy::FRONT_BOUND_SIZE;

            constexpr auto expectedSignature = "aaaa";
            CHECK(memcmp(front, expectedSignature, 4) == 0);
        }

        SECTION("signs the allocation with the end bound signature")
        {
            using BoundsPolicy = StandardBoundsPolicy<Token<'a'>, Token<'z'>>;
            tov::memory::arena::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);
            auto ptr = arena.allocate();
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
            tov::memory::arena::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);
            void* ptr = arena.allocate();

            CHECK_THROWS_AS(arena.deallocate(ptr), tov::memory::BoundsCheckException);
        }

        SECTION("throws an error when the end signature check fails")
        {
            using BoundsPolicy = StandardBoundsPolicy<TokenTrue, TokenFalse>;
            tov::memory::arena::TypedMemoryArena<int, AllocationPolicy, AlignmentPolicy, ThreadPolicy, BoundsPolicy> arena(start, end);
            void* ptr = arena.allocate();

            CHECK_THROWS_AS(arena.deallocate(ptr), tov::memory::BoundsCheckException);
        }
    }
}
