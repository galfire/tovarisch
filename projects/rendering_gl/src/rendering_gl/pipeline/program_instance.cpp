#include <rendering_gl/pipeline/program_instance.h>

#include <rendering_gl/pipeline/shader.h>

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

#include <iostream>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    ProgramInstance::ProgramInstance(
        size_t constantBufferSize,
        rendering::pipeline::ProgramState::ConstantBufferOffsetMap const& constantBufferOffsetMap
    )
        : rendering::pipeline::ProgramInstance(constantBufferSize, constantBufferOffsetMap)
    {
        auto op = log_gl_op("create program");
        mProgramID = glCreateProgram();
    }

    ProgramInstance::~ProgramInstance()
    {
        auto op = log_gl_op("delete program");
        glDeleteProgram(mProgramID);
    }

    void ProgramInstance::attachShaderImpl(rendering::pipeline::Shader& shader)
    {
        auto& s = static_cast<Shader&>(shader);
        auto shaderID = s.getShaderID();
        auto op = log_gl_op("attach shader", mProgramID, shaderID);
        glAttachShader(mProgramID, shaderID);
    }

    void ProgramInstance::detachShaderImpl(rendering::pipeline::Shader& shader)
    {
        auto& s = static_cast<Shader&>(shader);
        auto shaderID = s.getShaderID();
        auto op = log_gl_op("detach shader", mProgramID, shaderID);
        glDetachShader(mProgramID, shaderID);
    }

    void ProgramInstance::linkImpl() const
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

    void ProgramInstance::useImpl() const
    {
        auto op = log_gl_op("use program", mProgramID);
        glUseProgram(mProgramID);
    }

    auto ProgramInstance::getUniformLocation(const char* name) const -> int
    {
        auto op = log_gl_op("get uniform location", name);
        auto location = glGetUniformLocation(mProgramID, name);
        assert(location >= 0);
        return location;
    }

    void ProgramInstance::setMatrix4(const char* name, const math::Matrix4& value) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set matrix4", name);
        glUniformMatrix4fv(
            location,
            1,
            GL_FALSE,
            // Transpose row major to GL column major
            value.transpose().data()
        );
    }

    void ProgramInstance::setVector2(const char* name, const math::Vector2& value) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set vector2", name);
        glUniform2fv(
            location,
            1,
            value.data()
        );
    }

    void ProgramInstance::setVector3(const char* name, const math::Vector3& value) const
    {
        auto location = getUniformLocation(name);
        auto op = log_gl_op("set vector3", name);
        glUniform3fv(
            location,
            1,
            value.data()
        );
    }

    void ProgramInstance::setVector4(const char* name, const math::Vector4& value) const
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
