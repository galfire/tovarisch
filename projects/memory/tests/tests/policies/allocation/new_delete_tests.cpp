#include "test_helper.h"

#include <tov/memory/policies/allocation/new_delete.h>

TEST_CASE("NewDelete", "[NewDelete]")
{
    tov::memory::policies::allocation::NewDelete policy;

    SECTION("allocate")
    {
        SECTION("returns a valid pointer")
        {
            void* ptr = policy.allocate(64);
            CHECK(ptr != nullptr);
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

        SECTION("deallocates the pointer")
        {
            policy.deallocate(ptr);

            // TODO: CHECK something
        }
    }
}
