#ifndef TOV_MEMORY_POLICIES_BOUNDS_NONE_H
#define TOV_MEMORY_POLICIES_BOUNDS_NONE_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(bounds)

    class None
    {
    public:
        constexpr static size_t FRONT_BOUND_SIZE = 0;
        constexpr static size_t END_BOUND_SIZE = 0;
        constexpr static size_t TOTAL_BOUND_SIZE = FRONT_BOUND_SIZE + END_BOUND_SIZE;

    public:
        inline void signFront(void* memory) {}
        inline void signEnd(void* memory) {}

        inline bool checkFrontSignature(void* memory) const { return true; }
        inline bool checkEndSignature(void* memory) const { return true; }
    };

    TOV_NAMESPACE_END // bounds
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#endif
