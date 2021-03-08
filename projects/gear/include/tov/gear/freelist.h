#ifndef TOV_GEAR_FREELIST_H
#define TOV_GEAR_FREELIST_H

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(gear)

    class Freelist
    {
    public:
        Freelist(void* start, void* end, size_t elementSize);
        auto getBlock() -> void *;
        auto returnBlock(void* ptr) -> void;
        auto reset(void* start, void* end, size_t elementSize) -> void;

    private:
        Freelist* mNext = nullptr;
    };

    TOV_NAMESPACE_END // gear
}

#endif 
