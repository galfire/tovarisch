#include "rendering_gl/pipeline/program.h"

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

#include <iostream>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    Program::Program()
        : rendering::pipeline::Program()
    {
        auto op = log_gl_op("create program");
        mProgramID = glCreateProgram();
    }

    Program::~Program()
    {
        auto op = log_gl_op("delete program");
        glDeleteProgram(mProgramID);
    }

    void Program::attachShaderImpl(rendering::pipeline::Shader& shader) const
    {
        auto& s = static_cast<Shader&>(shader);
        auto shaderID = s.getShaderID();
        auto op = log_gl_op("attach shader", mProgramID, shaderID);
        glAttachShader(mProgramID, shaderID);
    }

    void Program::detachShaderImpl(rendering::pipeline::Shader& shader) const
    {
        auto& s = static_cast<Shader&>(shader);
        auto shaderID = s.getShaderID();
        auto op = log_gl_op("detach shader", mProgramID, shaderID);
        glDetachShader(mProgramID, shaderID);
    }

    void Program::linkImpl() const
    {
        auto op = log_gl_op("link program", mProgramID);
        glLinkProgram(mProgramID);
        int success;
        glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
        if (!success)
        {
            const auto sz = 1024;
            char infoLog[sz];
            glGetProgramInfoLog(mProgramID, sz, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

    void Program::buildLocationMapImpl()
    {
        for (auto&& kv : mConstantBufferDescriptorMap)
        {
            auto uniformName = kv.first;
            auto uniformLocation = glGetUniformLocation(mProgramID, uniformName.c_str());
            assert(uniformLocation >= 0);
            mUniformLocationMap.emplace(uniformName, uniformLocation);
        }
    }

    void Program::useImpl() const
    {
        auto op = log_gl_op("use program", mProgramID);
        glUseProgram(mProgramID);
    }

    auto Program::getUniformLocation(std::string name) const -> int
    {
        return mUniformLocationMap.at(name);
    }

    void Program::setFloat(std::string name, float data) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set float", name);
        glUniform1f(
            location,
            data
        );
    }

    void Program::setInteger(std::string name, int data) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set integer", name);
        glUniform1i(
            location,
            data
        );
    }

    void Program::setVector2(std::string name, void const *const data) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set vector2", name);
        glUniform2fv(
            location,
            1,
            reinterpret_cast<GLfloat const *const>(data)
        );
    }

    void Program::setVector3(std::string name, void const *const data) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set vector3", name);
        glUniform3fv(
            location,
            1,
            static_cast<GLfloat const *const>(data)
        );
    }

    void Program::setVector4(std::string name, void const *const data) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set vector4", name);
        glUniform4fv(
            location,
            1,
            static_cast<GLfloat const* const>(data)
        );
    }

    void Program::setMatrix3(std::string name, void const* const data) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set matrix3", name);
        auto& matrix = *static_cast<math::Matrix4 const* const>(data);
        glUniformMatrix3fv(
            location,
            1,
            GL_FALSE,
            // Transpose row major to GL column major
            reinterpret_cast<GLfloat const* const>(matrix.transpose().data())
        );
    }

    void Program::setMatrix4(std::string name, void const* const data) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set matrix4", name);
        auto& matrix = *static_cast<math::Matrix4 const* const>(data);
        glUniformMatrix4fv(
            location,
            1,
            GL_FALSE,
            // Transpose row major to GL column major
            reinterpret_cast<GLfloat const* const>(matrix.transpose().data())
        );
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}
