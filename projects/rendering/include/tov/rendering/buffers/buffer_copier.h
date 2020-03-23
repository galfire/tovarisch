#ifndef TOV_RENDERING_BUFFERS_BUFFER_COPIER_H
#define TOV_RENDERING_BUFFERS_BUFFER_COPIER_H

#include <tov/rendering/rendering_core.h>

#include <cstring>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferCopier
    {
    public:
        BufferCopier(void*& src, void*& dst)
            : mSource(src)
            , mDestination(dst)
        {}
        virtual ~BufferCopier() = default;

        void operator () (size_t offset, size_t length)
        {
            byte* offsetDestination = static_cast<byte*>(mDestination) + offset;
            memcpy(offsetDestination, mSource, length);
        }

    protected:
        void*& mSource;
        void*& mDestination;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif
