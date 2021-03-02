#include "test_helper.h"

#include <tov/memory/bounds_signer.h>
#include <tov/memory/policies/bounds/simple.h>

TEST_CASE("BoundsSigner", "[BoundsSigner]")
{
    using BoundsPolicy = tov::memory::policies::bounds::Simple;
    tov::memory::BoundsSigner<BoundsPolicy> boundsSigner;

    unsigned char buffer[1024];
    memset(buffer, 0xCC, 1024);

    SECTION("signFront")
    {
        auto expectedSignature = BoundsPolicy::FRONT_BOUND_SIGNATURE;
        auto signatureSize = BoundsPolicy::FRONT_BOUND_SIZE;

        SECTION("signs the front of the buffer at the given pointer with the bounds policy front signature")
        {
            void* ptr = &buffer;
            boundsSigner.signFront(ptr);
            int compare = memcmp(expectedSignature, &buffer, signatureSize);
            bool success = compare == 0;
            CHECK(success);
            //CHECK(compare == 0);
        }

        SECTION("moves the given pointer forward by the size of the bounds policy front signature")
        {
            void* ptr = &buffer;
            boundsSigner.signFront(ptr);
            CHECK((uintptr_t)ptr == (uintptr_t)&buffer + signatureSize);
        }
    }

    SECTION("signEnd")
    {
        auto expectedSignature = BoundsPolicy::END_BOUND_SIGNATURE;
        auto signatureSize = BoundsPolicy::END_BOUND_SIZE;

        SECTION("signs the end of the buffer at the given pointer with the bounds policy end signature")
        {
            void* ptr = &buffer;
            boundsSigner.signEnd(ptr);
            int compare = memcmp(expectedSignature, &buffer, signatureSize);
            CHECK(compare == 0);
        }

        SECTION("moves the given pointer forward by the size of the bounds policy end signature")
        {
            void* ptr = &buffer;
            boundsSigner.signEnd(ptr);
            CHECK((uintptr_t)ptr == (uintptr_t)&buffer + signatureSize);
        }
    }
}