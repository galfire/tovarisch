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
        {
            auto instance = std::make_unique<MaterialInstance>(*this, mRasterizerStateDescriptor);
            mInstances.push_back(std::move(instance));
        }

        auto instance = mInstances.back().get();
        return *instance;
    }

    TOV_NAMESPACE_END // rendering
}
