#ifndef TOV_MEMORY_POLICIES_BOUNDS_TOKEN_H
#define TOV_MEMORY_POLICIES_BOUNDS_TOKEN_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(bounds)

    template <byte TOKEN>
    class Token
    {
    public:
        // Number of bytes in the bound 
        constexpr static size_t BOUND_SIZE = 4;
        constexpr static byte BOUND_TOKEN = TOKEN;
        constexpr static byte BOUND_SIGNATURE[BOUND_SIZE] = { BOUND_TOKEN, BOUND_TOKEN, BOUND_TOKEN, BOUND_TOKEN };

    public:
        void sign(void* memory)
        {
            memcpy(memory, BOUND_SIGNATURE, BOUND_SIZE);
        }

        bool checkSignature(void* memory) const
        {
            return memcmp(memory, BOUND_SIGNATURE, BOUND_SIZE) == 0;
        }
    };

    TOV_NAMESPACE_END // bounds
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#endif
