#ifndef TOV_RENDERING_BUFFERS_BUFFER_OBJECT_H
#define TOV_RENDERING_BUFFERS_BUFFER_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "buffer.h"
#include "lock_settings.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferObject
    {
    public:
        BufferObject(BufferBase& buffer) noexcept
            : mBuffer(buffer)
        {}
        
        virtual ~BufferObject() noexcept = default;

        auto lock(size_t offset, size_t length, LockSettings lockSettings)
        {
            return mBuffer.lock(offset, length, lockSettings);
        }

        auto lock(LockSettings lockSettings)
        {
            return mBuffer.lock(lockSettings);
        }

        void unlock()
        {
            mBuffer.unlock();
        }

        auto getBuffer() const -> auto& { return mBuffer; }

    private:
        BufferBase& mBuffer;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif
