#include "rendering/render_target.h"

#include "rendering/camera.h"
#include "rendering/render_system.h"
#include "rendering/viewport.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    RenderTarget::RenderTarget(
        uint width,
        uint height,
        PixelFormat pixelFormat
    ) noexcept 
        : mWidth(width)
        , mHeight(height)
        , mPixelFormat(pixelFormat)
    {}

    RenderTarget::~RenderTarget()
    {}

    auto RenderTarget::createViewport(
        int zIndex,
        float normalizedLeft,
        float normalizedTop,
        float normalizedWidth,
        float normalizedHeight,
        Colour backgroundColour
    ) -> Viewport&
    {
        auto viewport = std::unique_ptr<Viewport>(
            new Viewport(
                *this,
                zIndex,
                normalizedLeft,
                normalizedTop,
                normalizedWidth,
                normalizedHeight,
                backgroundColour
            ));
        mViewports.push_back(std::move(viewport));
        return *mViewports.back().get();
    }

    TOV_NAMESPACE_END
}
