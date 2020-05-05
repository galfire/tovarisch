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

    private:
        auto instantiateImpl() const -> rendering::pipeline::ProgramInstance* override;

    private:
        uint mProgramID;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
