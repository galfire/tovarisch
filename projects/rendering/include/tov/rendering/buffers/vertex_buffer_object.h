#ifndef TOV_RENDERING_BUFFERS_VERTEX_BUFFER_OBJECT_H
#define TOV_RENDERING_BUFFERS_VERTEX_BUFFER_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "buffer_object.h"

#include "vertex_buffer_format.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferBase;

    class VertexBufferObject
        : public BufferObject
    {
    public:
        VertexBufferObject(BufferBase& buffer)
            : BufferObject(buffer)
        {}
    };

    TOV_NAMESPACE_END // buffers 
    TOV_NAMESPACE_END // rendering
}

#endif
