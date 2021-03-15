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

    RenderTarget::~RenderTarget() noexcept
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
        {
            auto viewport = std::make_unique<Viewport>(
                *this,
                zIndex,
                normalizedLeft,
                normalizedTop,
                normalizedWidth,
                normalizedHeight,
                backgroundColour
            );
            mViewports.push_back(std::move(viewport));
        }
        
        auto viewport = mViewports.back().get();
        return *viewport;
    }

    TOV_NAMESPACE_END
}
