#ifndef TOV_RENDERING_GL_BUFFERS_BUFFER_H
#define TOV_RENDERING_GL_BUFFERS_BUFFER_H

#include <tov/rendering/buffers/buffer.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/usage_settings.h>
#include "buffer_binder.h"
#include "buffer_writer.h"

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(buffers)

    class NullReader
    {
    public:
        NullReader(void*& src, void*& dst, GLuint& bufferID, GLenum& bufferTarget) {}
        void operator () (size_t offset, size_t length) {}
    };

    template<
        rendering::buffers::UsageSettings usageSettings,
        rendering::buffers::AccessSettings accessSettings
    >
    class Buffer
        : public rendering::buffers::Buffer<NullReader, BufferWriter, usageSettings, accessSettings>
    {
    private:
        using AccessSettings = tov::rendering::buffers::AccessSettings;
        using UsageSettings = tov::rendering::buffers::UsageSettings;

        static GLenum getGLAccessSettings();
        static GLenum getGLUsageSettings();

    public:
        Buffer(
            rendering::buffers::BufferManagerBase& manager,
            size_t bytes,
            GLenum bufferTarget
        );
        ~Buffer();

        void discard() override;

    private:
        void map() override {}
        void unmap() override {}

        auto bind() { return BufferBinder(mBufferID, mBufferTarget); }

    private:
        GLuint mBufferID;
        GLenum mBufferTarget;
        static inline GLenum sGLUsageSettings = getGLUsageSettings();
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#include "buffer.inl"

#endif