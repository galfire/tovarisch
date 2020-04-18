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
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(buffers)

    namespace { namespace base = rendering::buffers; }

    class BufferManager
        : public base::BufferManager<BufferManager>
    {
    public:
        auto createIndexBufferImpl(size_t size)
        {
            constexpr auto usageSettings = buffers::UsageSettings::STATIC;
            constexpr auto accessSettings = buffers::AccessSettings::WRITE;
            return create<usageSettings, accessSettings>(size, GL_ELEMENT_ARRAY_BUFFER);
        }

        auto createVertexBufferImpl(size_t size)
        {
            constexpr auto usageSettings = buffers::UsageSettings::STATIC;
            constexpr auto accessSettings = buffers::AccessSettings::WRITE;
            return create<usageSettings, accessSettings>(size, GL_ARRAY_BUFFER);
        }

    protected:
        template<base::UsageSettings usageSettings, base::AccessSettings accessSettings>
        auto create(size_t size, GLenum bufferTarget)
        {
            using BufferT = Buffer<usageSettings, accessSettings>;
            return base::BufferManager<BufferManager>::create<BufferT>(size, bufferTarget);
        }
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_GL_BUFFERS_BUFFER_MANAGER_H
