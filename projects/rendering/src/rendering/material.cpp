#include <rendering/material.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Material::Material(pipeline::Program const& program) noexcept
        : mProgram(program)
    {
        //mTextureList.reserve(program.getNumTextures2D());
        mTextureList.reserve(1);
    }

    void Material::setTextureSlot(texture::Texture const* const texture, uint slot)
    {
        mTextureList[slot] = texture;
    }

    TOV_NAMESPACE_END // rendering
}
