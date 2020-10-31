#ifndef TOV_RENDERING_PIPELINE_TEXTURE_USAGE_H
#define TOV_RENDERING_PIPELINE_TEXTURE_USAGE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(texture)
    class Texture;
    TOV_NAMESPACE_END // texture
    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    struct TextureUsage
    {
        TextureUsage(texture::Texture const* texture, uint slot)
            : texture(texture)
            , slot(slot)
        {}

        texture::Texture const* texture = nullptr;
        uint slot = 0;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
