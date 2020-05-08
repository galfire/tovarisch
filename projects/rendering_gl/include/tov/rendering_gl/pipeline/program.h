#ifndef TOV_RENDERING_GL_PIPELINE_PROGRAM_H
#define TOV_RENDERING_GL_PIPELINE_PROGRAM_H

#include <tov/rendering/pipeline/program.h>

#include "shader.h"

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class ProgramInstance;

    TOV_NAMESPACE_END // pipeline

    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Program
        : public rendering::pipeline::Program
    {
    public:
        Program();
        ~Program();

        void setMatrix4(std::string name, void const *const data) const override;
        void setVector2(std::string name, void const *const data) const override;
        void setVector3(std::string name, void const *const data) const override;
        void setVector4(std::string name, void const *const data) const override;

    private:
        void attachShaderImpl(rendering::pipeline::Shader& shader) const override;
        void detachShaderImpl(rendering::pipeline::Shader& shader) const override;
        void linkImpl() const override;
        void useImpl() const override;

        auto getUniformLocation(std::string name) const -> int;

    private:
        uint mProgramID;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
