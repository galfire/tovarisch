#include <rendering/material.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Material::Material() noexcept
    {
    }

    auto Material::instantiate() -> MaterialInstance&
    {
        auto instance = std::unique_ptr<MaterialInstance>(
            new MaterialInstance(*this, mRasterizerStateDescriptor)
        );
        mInstances.push_back(std::move(instance));
        auto ret = mInstances.back().get();
        return *ret;
    }

    TOV_NAMESPACE_END // rendering
}
