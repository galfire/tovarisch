#include "rendering/viewport.h"

#include "rendering/render_target.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Viewport::Viewport(
        RenderTarget& renderTarget,
        int zIndex,
        float normalizedLeft,
        float normalizedTop,
        float normalizedWidth,
        float normalizedHeight,
        Colour backgroundColor
    ) noexcept
        : mRenderTarget(renderTarget)
        , mZIndex(zIndex)
        , mNormalizedLeft(normalizedLeft)
        , mNormalizedTop(normalizedTop)
        , mNormalizedWidth(normalizedWidth)
        , mNormalizedHeight(normalizedHeight)
        , mBackgroundColour(backgroundColor)
        , mLeft(0)
        , mTop(0)
        , mWidth(0)
        , mHeight(0)
    {
        updateDimensions();
    }

    void Viewport::updateDimensions() noexcept
    {
        uint width = mRenderTarget.getWidth();
        uint height = mRenderTarget.getHeight();

        mLeft = static_cast<uint>(mNormalizedLeft * width);
        mTop = static_cast<uint>(mNormalizedTop * height);
        mWidth = static_cast<uint>(mNormalizedWidth * width);
        mHeight = static_cast<uint>(mNormalizedHeight * height);
    }

    TOV_NAMESPACE_END
}
