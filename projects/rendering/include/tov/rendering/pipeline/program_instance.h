#ifndef TOV_RENDERING_PIPELINE_PROGRAM_INSTANCE_H
#define TOV_RENDERING_PIPELINE_PROGRAM_INSTANCE_H

#include <tov/rendering/rendering_core.h>

#include "program_state.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Shader;

    class ProgramInstance
    {
        TOV_MOVABLE_ONLY(ProgramInstance)

    public:
        ProgramInstance(
            size_t constantBufferSize,
            ProgramState::ConstantBufferOffsetMap const& constantBufferOffsetMap
        )
            : mProgramState(constantBufferSize, constantBufferOffsetMap)
        {}

        virtual ~ProgramInstance() = default;

        template <class T>
        auto getConstant(const char* name) const -> auto const&
        {
            return mProgramState.template getConstant<T>(name);
        }

        template <class T>
        auto setConstant(const char* name, T const& value)
        {
            mProgramState.template setConstant<T>(name, value);
        }

        auto getProgramState() const -> auto const& { return mProgramState; }

        void attachShader(Shader& shader);

        void link() const;
        void use() const;

        virtual void setMatrix4(const char* name, const math::Matrix4& value) const TOV_ABSTRACT;
        virtual void setVector2(const char* name, const math::Vector2& value) const TOV_ABSTRACT;
        virtual void setVector3(const char* name, const math::Vector3& value) const TOV_ABSTRACT;
        virtual void setVector4(const char* name, const math::Vector4& value) const TOV_ABSTRACT;

    private:
        void detachShader(Shader& shader);

        virtual void attachShaderImpl(Shader& shader) TOV_ABSTRACT;
        virtual void detachShaderImpl(Shader& shader) TOV_ABSTRACT;

        virtual void linkImpl() const TOV_ABSTRACT;
        virtual void useImpl() const TOV_ABSTRACT;

    private:
        ProgramState mProgramState;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
