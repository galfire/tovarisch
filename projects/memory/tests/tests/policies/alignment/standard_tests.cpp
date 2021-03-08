#include "test_helper.h"

#include <cstring>

#include <tov/memory/policies/alignment/standard.h>

TEST_CASE("Standard", "[Standard]")
{
    tov::memory::policies::alignment::Standard policy;

    SECTION("align")
    {
        SECTION("returns a pointer aligned to the specified alignment when there is enough space")
        {
            const size_t alignment = 128;
            const size_t sz = 64;
            size_t space = 256;
            void* ptr = operator new(sz);
            void* alignedPtr = policy.align(alignment, sz, ptr, space);
            CHECK((uintptr_t)alignedPtr % alignment == 0);
        }
    }
}
