#ifndef TOV_RENDERING_BUFFERS_PIXEL_BUFFER_OBJECT_H
#define TOV_RENDERING_BUFFERS_PIXEL_BUFFER_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "buffer_object.h"
#include "guard.h"

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

        auto getPixelFormat() const { return mPixelFormat; }

        auto updatePixelData(void const* const data, size_t size) -> void
        {
            auto guard = rendering::buffers::Guard(*this, rendering::buffers::LockSettings::WRITE);
            auto lock = guard.getLock();
            memcpy(lock, data, size);
        }

    private:
        PixelFormat mPixelFormat;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif
