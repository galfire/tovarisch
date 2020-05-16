#ifndef TOV_RENDERING_GL_TEXTURE_TEXTURE_H
#define TOV_RENDERING_GL_TEXTURE_TEXTURE_H

#include <tov/rendering/texture/texture.h>
#include <tov/rendering_gl/gpu_resource.h>

#include <tov/rendering/buffers/buffer_manager.h>

#include <tov/rendering_gl/buffers/buffer.h>
#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(texture)

    class TextureBinder
    {
    public:
        TextureBinder(GLuint textureID, GLenum textureTarget)
            : mTextureID(textureID)
            , mTextureTarget(textureTarget)
        {
            auto op = log_gl_op("bind texture", mTextureTarget, mTextureID);
            glBindTexture(mTextureTarget, mTextureID);
        }

        ~TextureBinder()
        {
            auto op = log_gl_op("unbind texture", mTextureTarget, mTextureID);
            glBindTexture(mTextureTarget, 0);
        }

    private:
        GLuint mTextureID;
        GLenum mTextureTarget;
    };

    class Texture2D
        : public rendering::texture::Texture2D
        , public GPUResource<TextureBinder>
    {
    public:
        Texture2D(
            rendering::buffers::PixelBufferObject& pbo,
            uint width,
            uint height,
            PixelFormat pixelFormat
        )
            : rendering::texture::Texture2D(pbo, width, height, pixelFormat)
        {
            glGenTextures(1, &mTextureID);
            
            auto textureBind = bind();

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
            {
                auto op = log_gl_op("pixel store alignment");
                glPixelStorei(GL_UNPACK_ALIGNMENT, pixelFormat.getSize());
            }
        }

        auto bind() const -> TextureBinder override { return TextureBinder(mTextureID, GL_TEXTURE_2D); }

        auto getPixelBuffer() const -> auto&
        {
            constexpr auto usageSettings = buffers::UsageSettings::STREAM;
            constexpr auto accessSettings = buffers::AccessSettings::WRITE;
            using Buffer = buffers::Buffer<usageSettings, accessSettings>;
            auto& buffer = static_cast<Buffer&>(mPBO.getBuffer());
            return buffer;
        }

        auto unpackPixelData() const -> void override
        {
            auto& buffer = getPixelBuffer();

            // Upload PBO data to texture
            auto textureBind = bind();
            auto bufferBind = buffer.bind();
            auto op = log_gl_op("tex subimage2D");
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        }

    private:
        GLuint mTextureID;
    };

    TOV_NAMESPACE_END // texture
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
