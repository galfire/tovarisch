#include "gear/freelist.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(gear)

    Freelist::Freelist(void* start, void* end, size_t elementSize)
    {
        reset(start, end, elementSize);
    }

    auto Freelist::getBlock() -> void*
    {
        if (mNext == nullptr)
        {
            return nullptr;
        }

        auto head = mNext;
        mNext = head->mNext;
        return head;
    }

    auto Freelist::returnBlock(void* ptr) -> void
    {
        auto head = static_cast<Freelist*>(ptr);
        head->mNext = mNext;
        mNext = head;
    }

    auto Freelist::reset(void* start, void* end, size_t elementSize) -> void
    {
        auto const numElements = ((uintptr_t)end - (uintptr_t)start) / elementSize;
        auto cursor = start;
        auto runner = this;
        for (auto i = 0; i < numElements; i++)
        {
            runner->mNext = static_cast<Freelist*>(cursor);
            runner = runner->mNext;
            cursor = static_cast<byte*>(cursor) + elementSize;
        }
        runner->mNext = nullptr;
    }

    TOV_NAMESPACE_END // gear
}
