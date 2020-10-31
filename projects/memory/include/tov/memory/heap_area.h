#ifndef TOV_MEMORY_HEAP_AREA_H
#define TOV_MEMORY_HEAP_AREA_H

#include <memory>

#include <tov/core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    class HeapArea
    {
    public:
        inline explicit HeapArea(const size_t size) noexcept;
        inline ~HeapArea() noexcept = default;

        inline size_t getSize() const noexcept;
        inline void* getStart() const noexcept;
        inline void* getEnd() const noexcept;

    private:
        void* mStart = nullptr;
        void* mEnd = nullptr;

        using ByteArrayUPtr = std::unique_ptr<byte[]>;
        ByteArrayUPtr mByteArray = nullptr;
    };

    using HeapAreaUPtr = std::unique_ptr<HeapArea>;

    TOV_NAMESPACE_END
}

#include "heap_area.inl"

#endif
