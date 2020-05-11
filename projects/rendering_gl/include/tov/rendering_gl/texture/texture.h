#ifndef TOV_RENDERING_GL_TEXTURE_TEXTURE_H
#define TOV_RENDERING_GL_TEXTURE_TEXTURE_H

#include <tov/rendering/texture/texture.h>

#include <tov/rendering/buffers/buffer_manager.h>
#include <tov/rendering/buffers/guard.h>
#include <tov/rendering/buffers/lock_settings.h>

#include <tov/rendering_gl/buffers/buffer.h>
#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(texture)

    class Texture2D
        : public rendering::texture::Texture2D
    {
    public:
        Texture2D(
            rendering::buffers::BufferManagerBase& bufferManager,
            uint width,
            uint height,
            PixelFormat pixelFormat
        )
            : rendering::texture::Texture2D(bufferManager, width, height, pixelFormat)
        {
            glGenTextures(1, &textureId);
            bind();
            {
                auto op = log_gl_op("set texture min filter");
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }
            {
                auto op = log_gl_op("set texture mag filter");
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
            //{
            //    auto op = log_gl_op("set texture wrap s");
            //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            //}
            //{
            //    auto op = log_gl_op("set texture wrap t");
            //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            //}
            {
                auto op = log_gl_op("tex image2D");
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            }
            unbind();
        }

        auto bind() const -> void
        {
            auto op = log_gl_op("bind texture2D");
            glBindTexture(GL_TEXTURE_2D, textureId);
        }

        auto unbind() const -> void
        {
            auto op = log_gl_op("unbind texture2D");
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        auto updatePixelData(void const* const data) const -> void override
        {
            auto pixelFormat = mPBO->getPixelFormat();

            {
                auto& pbo = *mPBO.get();
                auto guard = rendering::buffers::Guard(pbo, rendering::buffers::LockSettings::WRITE);
                auto lock = guard.getLock();
                memcpy(lock, data, mSize);
            }

            // Upload PBO data to texture
            //bind();
            {
                auto op = log_gl_op("tex subimage2D");
                auto& pbo = *mPBO.get();
                constexpr auto usageSettings = buffers::UsageSettings::STREAM;
                constexpr auto accessSettings = buffers::AccessSettings::WRITE;
                using Buffer = buffers::Buffer<usageSettings, accessSettings>;
                auto& buffer = static_cast<Buffer&>(pbo.getBuffer());
                auto bind = buffer.bind();

                {
                    auto op = log_gl_op("pixel store alignment");
                    glPixelStorei(GL_UNPACK_ALIGNMENT, pixelFormat.getSize());
                }

                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            }
            //unbind();
        }

    private:
        GLuint textureId;
    };

    TOV_NAMESPACE_END // texture
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
