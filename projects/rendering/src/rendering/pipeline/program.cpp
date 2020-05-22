#include "rendering/pipeline/program.h"

#include "rendering/pipeline/shader.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    auto Program::instantiate() -> ProgramInstance&
    {
        auto instance = std::unique_ptr<ProgramInstance>(
            new ProgramInstance(*this, mConstantBufferSize, mConstantBufferDescriptorMap)
        );
        mInstances.push_back(std::move(instance));
        auto ret = mInstances.back().get();
        return *ret;
    }

    void Program::attachShader(Shader& shader)
    {
        mShaders.push_back(shader);
        attachShaderImpl(shader);

        // TODO: Parse shader source and automatically add constant definitions
    }

    void Program::detachShader(Shader& shader) const
    {
        detachShaderImpl(shader);
    }

    void Program::link() const
    {
        linkImpl();

        // Always detach shaders after the program is linked
        for (auto&& shader : mShaders)
        {
            detachShader(shader);
        }
    }

    void Program::buildLocationMap()
    {
        buildLocationMapImpl();
    }

    void Program::use() const
    {
        useImpl();
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
