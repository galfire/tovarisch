#include "rendering_gl/pipeline/shader.h"

#include <iostream>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    GLenum Shader::getGLShaderType(rendering::pipeline::ShaderType shaderType)
    {
        switch (shaderType)
        {
        case rendering::pipeline::ShaderType::VERTEX:
            return GL_VERTEX_SHADER;
        case rendering::pipeline::ShaderType::FRAGMENT:
            return GL_FRAGMENT_SHADER;
        default:
            return 0;
        }
    }

    Shader::Shader(rendering::pipeline::ShaderType shaderType, const char* sourceFilePath)
        : rendering::pipeline::Shader(shaderType, sourceFilePath)
    {
        {
            auto glShaderType = getGLShaderType(shaderType);
            auto op = log_gl_op("create shader", glShaderType);
            mShaderID = glCreateShader(glShaderType);
        }
        {
            auto op = log_gl_op("shader source");
            auto source = mSource;
            glShaderSource(mShaderID, 1, &source, nullptr);
        }
    }

    Shader::~Shader()
    {
        auto op = log_gl_op("delete shader", mShaderID);
        glDeleteShader(mShaderID);
    }

    void Shader::compileImpl()
    {
        {
            auto op = log_gl_op("compile shader");
            glCompileShader(mShaderID);
            int success;
            glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                const auto sz = 1024;
                char infoLog[sz];
                glGetShaderInfoLog(mShaderID, sz, nullptr, infoLog);
                std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}
