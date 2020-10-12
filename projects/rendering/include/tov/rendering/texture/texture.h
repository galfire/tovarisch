#ifndef TOV_RENDERING_TEXTURE_TEXTURE_H
#define TOV_RENDERING_TEXTURE_TEXTURE_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/render_target.h>

#include <tov/rendering/pixel_format.h>

#include <tov/rendering/buffers/buffer_manager.h>
#include <tov/rendering/buffers/guard.h>
#include <tov/rendering/buffers/lock_settings.h>
#include <tov/rendering/buffers/pixel_buffer_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(texture)

    class Texture
    {
    public:
        Texture(uint numPixels, PixelFormat pixelFormat)
            : mPBO(nullptr)
            , mNumPixels(numPixels)
            , mPixelFormat(pixelFormat)
        {
            mSize = mPixelFormat.getSize() * mNumPixels;
        }

        virtual ~Texture() = default;

        auto getSize() const { return mSize; }
        auto getNumPixels() const { return mNumPixels; }
        auto getPixelFormat() const { return mPixelFormat; }

        void setPixelBufferObject(buffers::PixelBufferObject& pbo)
        {
            mPBO = &pbo;
        }

        virtual auto unpackPixelData() const -> void TOV_ABSTRACT;

    protected:
        uint mNumPixels;
        PixelFormat mPixelFormat;
        size_t mSize;
        
        buffers::PixelBufferObject* mPBO;
    };

    class Texture2D
        : public Texture
        , public RenderTarget
    {
    public:
        Texture2D(
            uint width,
            uint height,
            PixelFormat pixelFormat
        )
            : Texture(width * height, pixelFormat)
            , RenderTarget(width, height, pixelFormat)
        {}

        virtual ~Texture2D() = default;

        void swapBuffers() override {}
    };

    TOV_NAMESPACE_END // texture
    TOV_NAMESPACE_END // rendering
}

#endif
