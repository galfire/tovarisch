namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    inline HeapArea::HeapArea(const size_t size) noexcept
    {
        mByteArray = std::make_unique<byte[]>(size);
        byte* heap = mByteArray.get();
        mStart = heap;
        mEnd = heap + size;
    }

    inline size_t HeapArea::getSize() const noexcept
    {
        return (uintptr_t)mEnd - (uintptr_t)mStart;
    }

    inline void* HeapArea::getStart() const noexcept
    {
        return mStart;
    }

    inline void* HeapArea::getEnd() const noexcept
    {
        return mEnd;
    }

    TOV_NAMESPACE_END
}
