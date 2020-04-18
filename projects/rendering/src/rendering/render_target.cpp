#include "rendering/render_target.h"

#include "rendering/camera.h"
#include "rendering/render_system.h"
#include "rendering/viewport.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    RenderTarget::RenderTarget(
        RenderSystem& renderSystem,
        uint width,
        uint height,
        PixelFormat pixelFormat
    ) noexcept 
        : mRenderSystem(renderSystem)
        , mWidth(width)
        , mHeight(height)
        , mPixelFormat(pixelFormat)
    {}

    auto RenderTarget::createViewport(
        Camera& camera,
        int zIndex,
        float normalizedLeft,
        float normalizedTop,
        float normalizedWidth,
        float normalizedHeight,
        Colour backgroundColour
    ) -> Viewport*
    {
        auto viewport = std::unique_ptr<Viewport>(
            new Viewport(
                mRenderSystem,
                *this,
                camera,
                zIndex,
                normalizedLeft,
                normalizedTop,
                normalizedWidth,
                normalizedHeight,
                backgroundColour
            ));
        mViewports.push_back(std::move(viewport));
        return mViewports.back().get();
    }

    void RenderTarget::queueViewports()
    {
        for (auto&& viewport : mViewports)
        {
            viewport->queue();
        }
    }

    TOV_NAMESPACE_END
}
