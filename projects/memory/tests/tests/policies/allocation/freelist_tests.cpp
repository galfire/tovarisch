#include "test_helper.h"

#include <tov/memory/policies/allocation/freelist.h>

TEST_CASE("Freelist", "[Freelist]")
{
    const size_t sz = 1024;
    unsigned char buffer[sz];
    memset(buffer, 0xFF, sz);
    void* start = &buffer[0];
    void* end = &buffer[0] + sz;
    const size_t elementSize = 64;
    tov::memory::policies::allocation::Freelist policy(start, end, elementSize);

    SECTION("allocate")
    {
        SECTION("returns a valid pointer")
        {
            void* ptr = policy.allocate();
            CHECK(ptr != nullptr);
        }

        SECTION("returns a pointer in the buffer")
        {
            void* ptr = policy.allocate();
            CHECK(ptr >= start);
            CHECK(ptr < end);
        }

        SECTION("returns nullptr when the allocation size is greater than the remaining space in the buffer")
        {
            auto n = sz / elementSize;
            for (auto i = 0; i < n; i++)
                REQUIRE_NE(policy.allocate(), nullptr);

            CHECK_EQ(policy.allocate(), nullptr);
        }

        SECTION("allocates space for type construction")
        {
            void* ptr = policy.allocate();
            int* value = new (ptr) int(42);
            CHECK(value == ptr);
            CHECK(*value == 42);
        }
    }

    SECTION("deallocate")
    {
        void* ptr = policy.allocate();

        SECTION("does nothing")
        {
            unsigned char original[sz];
            memcpy(original, buffer, sz);

            policy.deallocate(ptr);

            int compare = memcmp(buffer, original, sz);
            CHECK(compare == 0);
        }
    }

    SECTION("reset")
    {
        SECTION("allows allocations to reuse the buffer")
        {
            void* ptr = policy.allocate();
            policy.reset();
            void* ptr2 = policy.allocate();
            CHECK(ptr == ptr2);
        }
    }
}
