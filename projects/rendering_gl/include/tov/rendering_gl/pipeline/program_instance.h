#ifndef TOV_RENDERING_GL_PIPELINE_INSTANCE_PROGRAM_H
#define TOV_RENDERING_GL_PIPELINE_INSTANCE_PROGRAM_H

#include <tov/rendering/pipeline/program_instance.h>

#include <tov/rendering/pipeline/program_state.h>

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    class ProgramInstance
        : public rendering::pipeline::ProgramInstance
    {
    public:
        ProgramInstance(
            size_t constantBufferSize,
            rendering::pipeline::ProgramState::ConstantBufferOffsetMap const& constantBufferOffsetMap
        );
        ~ProgramInstance();

        void setMatrix4(const char* name, const math::Matrix4& value) const override;
        void setVector2(const char* name, const math::Vector2& value) const override;
        void setVector3(const char* name, const math::Vector3& value) const override;
        void setVector4(const char* name, const math::Vector4& value) const override;

        void attachShaderImpl(rendering::pipeline::Shader& shader) override;
        void detachShaderImpl(rendering::pipeline::Shader& shader) override;
        void linkImpl() const override;
        void useImpl() const override;

    private:
        auto getUniformLocation(const char* name) const -> int;

    private:
        uint mProgramID;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
