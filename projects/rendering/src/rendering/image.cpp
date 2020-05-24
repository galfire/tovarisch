#include <rendering/image.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Image::Image(const char* path)
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

    TOV_NAMESPACE_END
}
