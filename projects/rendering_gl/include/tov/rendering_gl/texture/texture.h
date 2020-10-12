#ifndef TOV_RENDERING_GL_TEXTURE_TEXTURE_H
#define TOV_RENDERING_GL_TEXTURE_TEXTURE_H

#include <tov/rendering/texture/texture.h>
//#include <tov/rendering_gl/gpu_resource.h>

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
        //, public GPUResource<TextureBinder>
    {
    public:
        Texture2D(
            uint width,
            uint height,
            PixelFormat pixelFormat
        )
            : rendering::texture::Texture2D(width, height, pixelFormat)
        {
            glGenTextures(1, &mTextureID);
            
            auto bind = binder();

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
                // TODO: Determine GL pixel format from mPixelFormat
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            }
            {
                auto op = log_gl_op("pixel store alignment");
                glPixelStorei(GL_UNPACK_ALIGNMENT, pixelFormat.getSize());
            }
        }

        ~Texture2D()
        {}

        auto getPixelBuffer() const -> auto&
        {
            constexpr auto usageSettings = buffers::UsageSettings::STREAM;
            constexpr auto accessSettings = buffers::AccessSettings::WRITE;
            using Buffer = buffers::Buffer<usageSettings, accessSettings>;
            auto& buffer = static_cast<Buffer&>(mPBO->getBuffer());
            return buffer;
        }

        auto unpackPixelData() const -> void override
        {
            auto& buffer = getPixelBuffer();

            // Upload PBO data to texture
            auto textureBind = binder();
            auto bufferBind = buffer.binder();
            auto op = log_gl_op("tex subimage2D");
            // TODO: Determine GL pixel format from mPixelFormat
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        }

        auto getTextureID() const { return mTextureID; }

        void activate(uint slot) const
        {
            {
                auto op = log_gl_op("glActiveTexture", slot);
                glActiveTexture(GL_TEXTURE0 + slot);
            }
            {
                auto op = log_gl_op("glBindTexture", mTextureID);
                glBindTexture(GL_TEXTURE_2D, mTextureID);
            }
        }

        void deactivate(uint slot) const
        {
            {
                auto op = log_gl_op("glActiveTexture", slot);
                glActiveTexture(GL_TEXTURE0 + slot);
            }
            {
                auto op = log_gl_op("unbind texture", mTextureID);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

        auto binder() const -> TextureBinder { return TextureBinder(mTextureID, GL_TEXTURE_2D); }

    private:
        GLuint mTextureID;
    };

    TOV_NAMESPACE_END // texture
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
