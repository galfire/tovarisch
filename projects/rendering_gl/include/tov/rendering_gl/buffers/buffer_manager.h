#ifndef TOV_RENDERING_GL_BUFFERS_BUFFER_MANAGER_H
#define TOV_RENDERING_GL_BUFFERS_BUFFER_MANAGER_H

#include <tov/rendering/buffers/buffer_manager.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/index_type.h>
#include <tov/rendering/buffers/usage_settings.h>

#include <tov/rendering_gl/gl_impl.h>

#include "buffer.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferBase;

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(buffers)

    using rendering::buffers::AccessSettings;
    using rendering::buffers::UsageSettings;

    class BufferManager
        : public rendering::buffers::BufferManager<BufferManager>
    {
    public:
        template<UsageSettings usageSettings, AccessSettings accessSettings>
        auto createIndexBufferImpl(size_t size)
        {
            return create<usageSettings, accessSettings>(size, GL_ELEMENT_ARRAY_BUFFER);
        }

        template<UsageSettings usageSettings, AccessSettings accessSettings>
        auto createVertexBufferImpl(size_t size)
        {
            return create<usageSettings, accessSettings>(size, GL_ARRAY_BUFFER);
        }

    protected:
        template<UsageSettings usageSettings, AccessSettings accessSettings>
        auto create(size_t size, GLenum bufferTarget)
        {
            return rendering::buffers::BufferManager<BufferManager>::create<Buffer<usageSettings, accessSettings>>(size, bufferTarget);
        }
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_GL_BUFFERS_BUFFER_MANAGER_H
