#ifndef TOV_RENDERING_IMAGE_H
#define TOV_RENDERING_IMAGE_H

#include "rendering_core.h"

#include "pixel_format.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <tov/memory/heap_area.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Image
    {
    public:
        Image(const char* path)
            : mPixelFormat(8, 8, 8, 8, 0, 0)
        {
            stbi_set_flip_vertically_on_load(true);
            byte* image = stbi_load(
                path,
                &mWidth,
                &mHeight,
                &mChannels,
                STBI_rgb_alpha
            );

            uint numPixels = mWidth * mHeight;
            size_t size = numPixels * mChannels;
            mHeapArea = std::make_unique<memory::HeapArea>(size);
            memcpy(mHeapArea->getStart(), image, size);

            stbi_image_free(image);
        }

        ~Image() = default;

        auto data() const { return mHeapArea->getStart(); }
        auto getSize() const { return mHeapArea->getSize(); }
        auto getWidth() const { return mWidth; }
        auto getHeight() const { return mHeight; }

    private:
        int mWidth;
        int mHeight;
        int mChannels;

        PixelFormat mPixelFormat;

        std::unique_ptr<memory::HeapArea> mHeapArea;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
