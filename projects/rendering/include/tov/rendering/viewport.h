#ifndef TOV_RENDERING_VIEWPORT_H
#define TOV_RENDERING_VIEWPORT_H

#include "rendering_core.h"

#include "colour.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderTarget;

    class Viewport
    {
    public:
        explicit Viewport(
            RenderTarget& renderTarget,
            int zIndex,
            float normalizedLeft = 0.0f,
            float normalizedTop = 0.0f,
            float normalizedWidth = 1.0f,
            float normalizedHeight = 1.0f,
            Colour backgroundColour = Colour::Black
        ) noexcept;
        ~Viewport() noexcept = default;

        void updateDimensions() noexcept;

        auto getRenderTarget() -> auto& { return mRenderTarget; }
        auto getRenderTarget() const -> auto const& { return mRenderTarget; }
        auto getZIndex() const { return mZIndex; }
        auto getLeft() const { return mLeft; }
        auto getTop() const { return mTop; }
        auto getWidth() const { return mWidth; }
        auto getHeight() const { return mHeight; }
        auto getBackgroundColour() const { return mBackgroundColour; }

    protected:
        RenderTarget& mRenderTarget;

        int mZIndex;
        float mNormalizedLeft;
        float mNormalizedTop;
        float mNormalizedWidth;
        float mNormalizedHeight;

        uint mLeft;
        uint mTop;
        uint mWidth;
        uint mHeight;

        Colour mBackgroundColour;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
