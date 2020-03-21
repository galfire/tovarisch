#include "rendering/pipeline/program.h"

#include "rendering/pipeline/shader.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(pipeline)

	void Program::attachShader(Shader& shader)
    {
        // Compile ths shader if it's not already compiled
        shader.compile();
        mShaders.push_back(shader);
        attachShaderImpl(shader);
    }

    void Program::detachShader(Shader& shader)
    {
        detachShaderImpl(shader);
    }

    void Program::link()
    {
        linkImpl();

        // Always detach shaders after the program is linked
        for (auto&& shader : mShaders)
        {
            detachShader(shader);
        }
    }

    void Program::use()
    {
        useImpl();
    }

	TOV_NAMESPACE_END // pipeline
	TOV_NAMESPACE_END // rendering
}