#ifndef TOV_RENDERING_VIEWPORT_H
#define TOV_RENDERING_VIEWPORT_H

#include "rendering_core.h"

#include "colour.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;
    class RenderTarget;
    class Camera;

    class Viewport
    {
    public:
        explicit Viewport(
            RenderSystem& renderSystem,
            RenderTarget& renderTarget,
            Camera& camera,
            int zIndex,
            float normalizedLeft = 0.0f,
            float normalizedTop = 0.0f,
            float normalizedWidth = 1.0f,
            float normalizedHeight = 1.0f,
            Colour backgroundColour = Colour::Black
        ) noexcept;
        virtual ~Viewport() noexcept = default;

        void updateDimensions() noexcept;

        void queue() noexcept;
        
        void renderCamera();

        auto getRenderTarget() -> auto& { return mRenderTarget; }
        auto getZIndex() const { return mZIndex; }
        auto getLeft() const { return mLeft; }
        auto getTop() const { return mTop; }
        auto getWidth() const { return mWidth; }
        auto getHeight() const { return mHeight; }
        auto getBackgroundColour() const { return mBackgroundColour; }

    protected:
        RenderSystem& mRenderSystem;
        RenderTarget& mRenderTarget;
        Camera& mCamera;

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
