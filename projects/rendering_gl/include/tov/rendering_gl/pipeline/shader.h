#ifndef TOV_RENDERING_GL_PIPELINE_SHADER_H
#define TOV_RENDERING_GL_PIPELINE_SHADER_H

#include <tov/rendering/pipeline/shader.h>

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Shader
        : public rendering::pipeline::Shader
    {
        friend class ProgramInstance;

    private:
        static GLenum getGLShaderType(rendering::pipeline::ShaderType shaderType);

    public:
        Shader(rendering::pipeline::ShaderType shaderType, const char* sourceFilePath);
        ~Shader();

        void compileImpl() override;

    private:
        auto getShaderID() const { return mShaderID; }

    private:
        uint mShaderID;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
