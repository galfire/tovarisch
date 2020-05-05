#ifndef TOV_RENDERING_RENDER_TARGET_H
#define TOV_RENDERING_RENDER_TARGET_H

#include "rendering_core.h"

#include "colour.h"
#include "pixel_format.h"
#include "viewport.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Camera;
    class RenderSystem;

    class RenderTarget
    {
        TOV_MOVABLE_ONLY(RenderTarget)

    public:
        RenderTarget(
            RenderSystem& renderSystem,
            uint width,
            uint height,
            PixelFormat pixelFormat = PixelFormat::Default
        ) noexcept;
        virtual ~RenderTarget() noexcept = default;

        virtual void prerender() const {}

        virtual void swapBuffers() TOV_ABSTRACT;

        auto getWidth() const noexcept { return mWidth; }
        auto getHeight() const noexcept { return mHeight; }

        auto createViewport(
            Camera& camera,
            int zIndex,
            float normalizedLeft = 0.0f,
            float normalizedTop = 0.0f,
            float normalizedWidth = 1.0f,
            float normalizedHeight = 1.0f,
            Colour backgroundColour = Colour::Black
        ) -> Viewport&;

        void queueViewports();

    protected:
        RenderSystem& mRenderSystem;

        uint mWidth;
        uint mHeight;
        PixelFormat mPixelFormat;

        std::vector<std::unique_ptr<Viewport>> mViewports;
    };

    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_RENDER_TARGET_H
