#ifndef TOV_RENDERING_TEXTURE_TEXTURE_H
#define TOV_RENDERING_TEXTURE_TEXTURE_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/pixel_format.h>

#include <tov/rendering/buffers/buffer_manager.h>
#include <tov/rendering/buffers/pixel_buffer_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(texture)

    class Texture
    {
    public:
        Texture(buffers::BufferManagerBase& bufferManager, uint numPixels, PixelFormat pixelFormat)
            : mBufferManager(bufferManager)
            , mNumPixels(numPixels)
            , mPixelFormat(pixelFormat)
        {
            mSize = mPixelFormat.getSize() * mNumPixels;

            auto buffer = bufferManager.createPixelUnpackBuffer(mPixelFormat, mNumPixels);
            mPBO = std::unique_ptr<buffers::PixelBufferObject>(
                new buffers::PixelBufferObject(*buffer, mPixelFormat)
            );
        }

        auto getSize() const { return mSize; }
        auto getNumPixels() const { return mNumPixels; }
        auto getPixelFormat() const { return mPixelFormat; }

        virtual auto updatePixelData(void const* const data) const -> void TOV_ABSTRACT;

    protected:
        buffers::BufferManagerBase& mBufferManager;

        uint mNumPixels;
        PixelFormat mPixelFormat;
        size_t mSize;
        
        std::unique_ptr<buffers::PixelBufferObject> mPBO;
    };

    class Texture2D
        : public Texture
    {
    public:
        Texture2D(
            buffers::BufferManagerBase& bufferManager,
            uint width,
            uint height,
            PixelFormat pixelFormat
        )
            : Texture(bufferManager, width * height, pixelFormat)
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
