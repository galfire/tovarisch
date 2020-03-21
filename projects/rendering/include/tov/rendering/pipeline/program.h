#ifndef TOV_RENDERING_PIPELINE_PROGRAM_H
#define TOV_RENDERING_PIPELINE_PROGRAM_H

#include <tov/rendering/rendering_core.h>

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Shader;

    class Program
    {
    public:
        Program() = default;
        virtual ~Program() = default;

        void attachShader(Shader& shader);
        void link();
        void use();

        virtual void setMatrix4(const char* name, const math::Matrix4& value) TOV_ABSTRACT;
        virtual void setVector2(const char* name, const math::Vector2& value) TOV_ABSTRACT;
        virtual void setVector3(const char* name, const math::Vector3& value) TOV_ABSTRACT;
        virtual void setVector4(const char* name, const math::Vector4& value) TOV_ABSTRACT;

    private:
        void detachShader(Shader& shader);

        virtual void attachShaderImpl(Shader& shader) TOV_ABSTRACT;
        virtual void detachShaderImpl(Shader& shader) TOV_ABSTRACT;
        virtual void linkImpl() TOV_ABSTRACT;
        virtual void useImpl() TOV_ABSTRACT;

    private:
        std::vector<std::reference_wrapper<Shader>> mShaders;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif