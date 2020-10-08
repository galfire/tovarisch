#ifndef TOV_RENDERING_PIPELINE_TEXTURE_DESCRIPTOR_H
#define TOV_RENDERING_PIPELINE_TEXTURE_DESCRIPTOR_H

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

    struct TextureDescriptor
    {
        TextureDescriptor(texture::Texture const* texture, uint slot)
            : texture(texture)
            , slot(slot)
        {}

        texture::Texture const* texture = nullptr;
        uint slot = 0;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_PIPELINE_SHADER_TYPE_H
