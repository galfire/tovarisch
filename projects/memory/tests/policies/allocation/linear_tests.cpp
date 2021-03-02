#include "../../test_helper.h"

#include <tov/memory/policies/allocation/linear.h>

TEST_CASE("Linear", "[Linear]")
{
    const size_t sz = 1024;
    unsigned char buffer[sz];
    memset(buffer, 0xFF, sz);
    void* start = &buffer[0];
    void* end = &buffer[0] + sz;
    tov::memory::policies::allocation::Linear policy(start, end);

    SECTION("allocate")
    {
        SECTION("returns a valid pointer")
        {
            void* ptr = policy.allocate(64);
            CHECK(ptr != nullptr);
        }

        SECTION("returns a pointer in the buffer")
        {
            void* ptr = policy.allocate(64);
            CHECK(ptr >= start);
            CHECK(ptr < end);
        }

        SECTION("writes the allocation size to the buffer before the returned pointer")
        {
            void* ptr = policy.allocate(64);
            size_t allocation_size = *((size_t*)ptr - 1);
            CHECK(allocation_size == 64);
        }

        SECTION("throws an error when the allocation size is greater than the remaining space in the buffer")
        {
            CHECK_THROWS_AS(policy.allocate(sz * 10), std::bad_alloc);
        }

        SECTION("allocates space for type construction")
        {
            void* ptr = policy.allocate(sizeof(int));
            int* value = new (ptr) int(42);
            CHECK(value == ptr);
            CHECK(*value == 42);
        }
    }

    SECTION("deallocate")
    {
        void* ptr = policy.allocate(sizeof(int));

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
            void* ptr = policy.allocate(64);
            policy.reset();
            void* ptr2 = policy.allocate(64);
            CHECK(ptr == ptr2);
        }
    }

    SECTION("getAllocationSize")
    {
        void* ptr = policy.allocate(64);

        SECTION("returns the size of the allocation at the given pointer in bytes")
        {
            size_t allocation_size = policy.getAllocationSize(ptr);
            CHECK(allocation_size == 64);
        }
    }
}
