#ifndef TOV_RENDERING_TEXTURE_TEXTURE_H
#define TOV_RENDERING_TEXTURE_TEXTURE_H

#include <tov/rendering/rendering_core.h>

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
        Texture(buffers::PixelBufferObject& pbo, uint numPixels, PixelFormat pixelFormat)
            : mPBO(pbo)
            , mNumPixels(numPixels)
            , mPixelFormat(pixelFormat)
        {
            mSize = mPixelFormat.getSize() * mNumPixels;
        }

        auto getSize() const { return mSize; }
        auto getNumPixels() const { return mNumPixels; }
        auto getPixelFormat() const { return mPixelFormat; }

        virtual auto unpackPixelData() const -> void TOV_ABSTRACT;

    protected:
        uint mNumPixels;
        PixelFormat mPixelFormat;
        size_t mSize;
        
        buffers::PixelBufferObject& mPBO;
    };

    class Texture2D
        : public Texture
    {
    public:
        Texture2D(
            buffers::PixelBufferObject& pbo,
            uint width,
            uint height,
            PixelFormat pixelFormat
        )
            : Texture(pbo, width * height, pixelFormat)
            , mWidth(width)
            , mHeight(height)
        {}

    protected:
        uint mWidth;
        uint mHeight;
    };

    TOV_NAMESPACE_END // texture
    TOV_NAMESPACE_END // rendering
}

#endif
