#include "rendering/pipeline/shader.h"

#include <stdio.h>
#include <iostream>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    Shader::Shader(ShaderType shaderType, const char* sourceFilePath)
        : mShaderType(shaderType)
    {
        FILE* file = fopen(sourceFilePath, "r");
        if (!file)
        {
            std::cerr << "Cannot open file " << sourceFilePath << ".\n";
            assert(false);
        }

        fseek(file, 0, SEEK_END);
        mSourceLength = ftell(file);
        rewind(file);

        mSource = new char[mSourceLength + 1];
        size_t result = fread(mSource, 1, mSourceLength, file);
        if (result != mSourceLength)
        {
            std::cerr << "Cannot read file " << sourceFilePath << ".\n";
            assert(false);
        }

        mSource[mSourceLength] = '\0';

        fclose(file);
    }

    Shader::~Shader()
    {
        delete[] mSource;
    }

    void Shader::compile()
    {
        if (mCompiled) return;

        compileImpl();
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}