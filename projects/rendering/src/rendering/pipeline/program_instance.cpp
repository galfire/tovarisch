#include <rendering/pipeline/program_instance.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    void ProgramInstance::detachShader(Shader& shader)
    {
        detachShaderImpl(shader);
    }

    void ProgramInstance::attachShader(Shader& shader)
    {
        attachShaderImpl(shader);
    }

    void ProgramInstance::link() const
    {
        linkImpl();

        // Always detach shaders after the program is linked
        /*for (auto&& shader : mShaders)
        {
            detachShader(shader);
        }*/
    }

    void ProgramInstance::use() const
    {
        useImpl();
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
