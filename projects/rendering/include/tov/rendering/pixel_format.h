#ifndef TOV_RENDERING_PIXEL_FORMAT_H
#define TOV_RENDERING_PIXEL_FORMAT_H

#include <tov/core.h>

#include "definitions.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class PixelFormat
    {
    public:
        PixelFormat(ushort red, ushort blue, ushort green, ushort alpha, ushort depth, ushort stencil)
            : mBitsRed(red)
            , mBitsBlue(blue)
            , mBitsGreen(green)
            , mBitsAlpha(alpha)
            , mBitsDepth(depth)
            , mBitsStencil(stencil)
        {}
        virtual ~PixelFormat() = default;

        ushort getBitsRed() const { return mBitsRed; }
        ushort getBitsBlue() const { return mBitsBlue; }
        ushort getBitsGreen() const { return mBitsGreen; }
        ushort getBitsAlpha() const { return mBitsAlpha; }
        ushort getBitsColour() const { return getBitsRed() + getBitsBlue() + getBitsGreen(); }
        ushort getBitsColourAlpha() const { return getBitsColour() + getBitsAlpha(); }
        ushort getBitsDepth() const { return mBitsDepth; }
        ushort getBitsStencil() const { return mBitsStencil; }
        // Size of a pixel in bytes
        ushort getSize() const { return getBitsColourAlpha() / 8; }

    protected:
        ushort mBitsRed;
        ushort mBitsBlue;
        ushort mBitsGreen;
        ushort mBitsAlpha;
        ushort mBitsDepth;
        ushort mBitsStencil;

    public:
        static const PixelFormat Default;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
