#ifndef TOV_MEMORY_POLICIES_THREAD_SINGLE_H
#define TOV_MEMORY_POLICIES_THREAD_SINGLE_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(thread)

    class Single
    {
    public:
        inline void enter() {};
        inline void leave() {};
    };

    TOV_NAMESPACE_END // thread
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}

#endif
