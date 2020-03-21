#ifndef TOV_RENDERING_GL_PIPELINE_PROGRAM_H
#define TOV_RENDERING_GL_PIPELINE_PROGRAM_H

#include <tov/rendering/pipeline/program.h>

#include "shader.h"

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Program
        : public rendering::pipeline::Program
    {
    public:
        Program();
        ~Program();

        void setMatrix4(const char* name, const math::Matrix4& value) override;
        void setVector2(const char* name, const math::Vector2& value) override;
        void setVector3(const char* name, const math::Vector3& value) override;
        void setVector4(const char* name, const math::Vector4& value) override;

    private:
        void attachShaderImpl(rendering::pipeline::Shader& shader) override;
        void detachShaderImpl(rendering::pipeline::Shader& shader) override;
        void linkImpl() override;
        void useImpl() override;

        auto getUniformLocation(const char* name) const -> int;

    private:
        uint mProgramID;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
