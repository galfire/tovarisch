#ifndef TOV_RENDERING_GL_BUFFER_BINDER_H
#define TOV_RENDERING_GL_BUFFER_BINDER_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferBinder
    {
    public:
        BufferBinder(GLuint bufferID, GLenum bufferTarget)
            : mBufferID(bufferID)
            , mBufferTarget(bufferTarget)
        {
            auto op = log_gl_op("bind buffer", mBufferTarget, mBufferID);
            glBindBuffer(mBufferTarget, mBufferID);
        }

        ~BufferBinder()
        {
            auto op = log_gl_op("unbind buffer", mBufferTarget, mBufferID);
            glBindBuffer(mBufferTarget, 0);
        }

    private:
        GLuint mBufferID;
        GLenum mBufferTarget;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
