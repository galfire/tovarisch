#include "rendering/render_target.h"

#include "rendering/camera.h"
#include "rendering/commands/commands.h"
#include "rendering/commands/command_bucket.h"
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

    void RenderTarget::renderViewports()
    {
        for (auto&& viewport : mViewports)
        {
            auto& bucket = mRenderSystem.getFrameCommandBucket();
            auto& command = bucket.addCommand<commands::ApplyViewport>(viewport->getZIndex());
            command.viewport = viewport.get();

            //viewport->renderCamera();
        }
    }

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

    TOV_NAMESPACE_END
}