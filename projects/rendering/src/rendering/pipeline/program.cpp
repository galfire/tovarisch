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
            instantiateImpl()
        );

        for (auto&& shader : mShaders)
        {
            instance->attachShader(shader);
        }

        instance->link();

        mInstances.push_back(std::move(instance));
        auto ret = mInstances.back().get();
        return *ret;
    }

	void Program::attachShader(Shader& shader)
    {
        mShaders.push_back(shader);

        // TODO: Parse shader source and automatically add constant definitions
    }

	TOV_NAMESPACE_END // pipeline
	TOV_NAMESPACE_END // rendering
}