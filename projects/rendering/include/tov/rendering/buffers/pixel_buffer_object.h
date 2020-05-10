#ifndef TOV_RENDERING_BUFFERS_PIXEL_BUFFER_OBJECT_H
#define TOV_RENDERING_BUFFERS_PIXEL_BUFFER_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "buffer_object.h"

#include <tov/rendering/pixel_format.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferBase;

    class PixelBufferObject
        : public BufferObject
    {
    public:
        PixelBufferObject(BufferBase& buffer, PixelFormat pixelFormat)
            : BufferObject(buffer)
            , mPixelFormat(pixelFormat)
        {}

    private:
        PixelFormat mPixelFormat;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif
