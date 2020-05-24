#ifndef TOV_RENDERING_IMAGE_H
#define TOV_RENDERING_IMAGE_H

#include "rendering_core.h"

#include "pixel_format.h"

#include <tov/memory/heap_area.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Image
    {
    public:
        Image(const char* path);
        ~Image() = default;

        auto data() const { return mHeapArea->getStart(); }
        auto getSize() const { return mHeapArea->getSize(); }
        auto getPixelFormat() const { return mPixelFormat; }
        auto getWidth() const { return mWidth; }
        auto getHeight() const { return mHeight; }

    private:
        int mChannels;
        int mWidth;
        int mHeight;
  
        PixelFormat mPixelFormat;

        std::unique_ptr<memory::HeapArea> mHeapArea;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
