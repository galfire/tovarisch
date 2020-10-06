#include <rendering/material.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Material::Material(pipeline::Program& program) noexcept
        : mProgram(program)
    {
        mTextureList.reserve(program.getNumTextures2D());
    }

    void Material::setTextureSlot(texture::Texture const* const texture, uint slot)
    {
        mTextureList.emplace(mTextureList.begin() + slot, texture);
    }

    auto Material::instantiate() -> MaterialInstance&
    {
        auto& programInstance = mProgram.instantiate();

        auto instance = std::unique_ptr<MaterialInstance>(
            new MaterialInstance(programInstance, mRasterizerStateDescriptor)
        );
        mInstances.push_back(std::move(instance));
        auto ret = mInstances.back().get();
        return *ret;
    }

    TOV_NAMESPACE_END // rendering
}
