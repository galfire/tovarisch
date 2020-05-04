#include "rendering/viewport.h"

#include "rendering/camera.h"
#include "rendering/render_system.h"
#include "rendering/render_target.h"
#include "rendering/commands/commands.h"
#include "rendering/commands/command_bucket.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Viewport::Viewport(
        RenderSystem& renderSystem,
        RenderTarget& renderTarget,
        Camera& camera,
        int zIndex,
        float normalizedLeft,
        float normalizedTop,
        float normalizedWidth,
        float normalizedHeight,
        Colour backgroundColor
    ) noexcept
        : mRenderSystem(renderSystem)
        , mRenderTarget(renderTarget)
        , mCamera(camera)
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

    void Viewport::queue() noexcept
    {
        auto& bucket = mRenderSystem.getFrameCommandBucket();
        auto& command = bucket.addCommand<commands::ApplyViewport>(getZIndex());
        command.viewport = this;
    }

    void Viewport::renderCamera()
    {
        //mCamera.renderScene();
    }

    TOV_NAMESPACE_END
}