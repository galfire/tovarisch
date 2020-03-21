#include "rendering_gl/pipeline/program.h"

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

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

    void Program::attachShaderImpl(rendering::pipeline::Shader& shader)
    {
        auto& s = static_cast<Shader&>(shader);
        auto shaderID = s.getShaderID();
        auto op = log_gl_op("attach shader", mProgramID, shaderID);
        glAttachShader(mProgramID, shaderID);
    }

    void Program::detachShaderImpl(rendering::pipeline::Shader& shader)
    {
        auto& s = static_cast<Shader&>(shader);
        auto shaderID = s.getShaderID();
        auto op = log_gl_op("detach shader", mProgramID, shaderID);
        glDetachShader(mProgramID, shaderID);
    }

    void Program::linkImpl()
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

    void Program::useImpl()
    {
        auto op = log_gl_op("use program", mProgramID);
        glUseProgram(mProgramID);
    }

    auto Program::getUniformLocation(const char* name) const -> int
    {
        auto op = log_gl_op("get uniform location", name);
        auto location = glGetUniformLocation(mProgramID, name);
        assert(location >= 0);
        return location;
    }

    void Program::setMatrix4(const char* name, const math::Matrix4& value)
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set matrix4", name);
        glUniformMatrix4fv(
            location,
            1,
            GL_FALSE,
            value.data()
        );
    }

    void Program::setVector2(const char* name, const math::Vector2& value)
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set vector2", name);
        glUniform2fv(
            location,
            1,
            value.data()
        );
    }

    void Program::setVector3(const char* name, const math::Vector3& value)
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set vector3", name);
        glUniform3fv(
            location,
            1,
            value.data()
        );
    }

    void Program::setVector4(const char* name, const math::Vector4& value)
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set vector4", name);
        glUniform4fv(
            location,
            1,
            value.data()
        );
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}
