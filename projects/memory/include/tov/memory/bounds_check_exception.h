#ifndef TOV_MEMORY_BOUNDS_CHECK_EXCEPTION_H
#define TOV_MEMORY_BOUNDS_CHECK_EXCEPTION_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    class BoundsCheckException
        : public std::exception
    {
    public:
        BoundsCheckException(const char* msg) throw()
            : std::exception(msg)
        {
        }
    };

    TOV_NAMESPACE_END
}

#endif
