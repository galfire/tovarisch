namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)
    TOV_NAMESPACE_BEGIN(policies)
    TOV_NAMESPACE_BEGIN(allocation)

    inline Freelist::Freelist(void* start, void* end, size_t elementSize) noexcept
        : mFreelist(start, end, elementSize)
        , mStart(start)
        , mEnd(end)
        , mElementSize(elementSize)
    {
    }

    inline auto Freelist::allocate() -> void*
    {
        return mFreelist.getBlock();
    }

    inline auto Freelist::deallocate(void* ptr) noexcept -> void
    {
        mFreelist.returnBlock(ptr);
    }

    inline auto Freelist::reset() noexcept -> void
    {
        mFreelist.reset(mStart, mEnd, mElementSize);
    }

    TOV_NAMESPACE_END // allocation
    TOV_NAMESPACE_END // policies
    TOV_NAMESPACE_END // memory
}
