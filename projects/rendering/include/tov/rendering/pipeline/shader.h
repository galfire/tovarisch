#ifndef TOV_RENDERING_PIPELINE_SHADER_H
#define TOV_RENDERING_PIPELINE_SHADER_H

#include <tov/rendering/rendering_core.h>

#include <tov/memory/heap_area.h>

#include "shader_type.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Shader
    {
        TOV_MOVABLE_ONLY(Shader)

    public:
        Shader(ShaderType shaderType, const char* sourceFilePath);
        virtual ~Shader();

        void compile();

    private:
        virtual void compileImpl() TOV_ABSTRACT;

    protected:
        bool mCompiled = false;

        ShaderType mShaderType;
        int mSourceLength = 0;
        char* mSource;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_PIPELINE_SHADER_H
