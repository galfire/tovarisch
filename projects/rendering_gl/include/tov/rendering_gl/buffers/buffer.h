#ifndef TOV_RENDERING_GL_BUFFERS_BUFFER_H
#define TOV_RENDERING_GL_BUFFERS_BUFFER_H

#include <tov/rendering/buffers/buffer.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/usage_settings.h>

#include <tov/rendering_gl/bindable.h>

#include "buffer_binder.h"
#include "buffer_writer.h"

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(buffers)

    namespace
    { 
        namespace base = rendering::buffers;
        using AccessSettings = base::AccessSettings;
        using UsageSettings = base::UsageSettings;
    }

    class NullReader
    {
    public:
        NullReader(void*& src, void*& dst, GLuint& bufferID, GLenum& bufferTarget) {}
        void operator () (size_t offset, size_t length) {}
    };

    template<
        UsageSettings usageSettings,
        AccessSettings accessSettings
    >
    class Buffer
        : public base::Buffer<NullReader, BufferWriter, usageSettings, accessSettings>
        , public Bindable
    {
    private:
        static constexpr GLenum getGLAccessSettings(); // TODO: AccessSettings is not used
        static constexpr GLenum getGLUsageSettings()
        {
            GLenum usage = 0;
            if ((usageSettings & UsageSettings::STATIC) == UsageSettings::STATIC)
            {
                usage = GL_STATIC_DRAW;
            }
            else if ((usageSettings & UsageSettings::DYNAMIC) == UsageSettings::DYNAMIC)
            {
                usage = GL_DYNAMIC_DRAW;
            }
            else if ((usageSettings & UsageSettings::STREAM) == UsageSettings::STREAM)
            {
                usage = GL_STREAM_DRAW;
            }
            return usage;
        }

    public:
        Buffer(
            base::BufferManagerBase& manager,
            size_t bytes,
            GLenum bufferTarget
        );
        ~Buffer();

        void bind() const override;
        void unbind() const override;

        auto binder() const -> BufferBinder { return BufferBinder(mBufferID, mBufferTarget); }

    private:
        void discard() override;

        void map() override {}
        void unmap() override {}

    private:
        GLuint mBufferID;
        GLenum mBufferTarget;
        static constexpr GLenum sGLUsageSettings = getGLUsageSettings();
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#include "buffer.inl"

#endif
