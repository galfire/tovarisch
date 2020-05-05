#ifndef TOV_RENDERING_PIPELINE_PROGRAM_H
#define TOV_RENDERING_PIPELINE_PROGRAM_H

#include <tov/rendering/rendering_core.h>

#include "constant_definition.h"
#include "program_instance.h"

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Shader;

    class Program
    {
        TOV_MOVABLE_ONLY(Program)

    public:
        using ShaderList = std::vector<std::reference_wrapper<Shader>>;

    public:
        Program() = default;
        virtual ~Program() = default;

        template<class T>
        void addConstantDefinition(const char* name, ConstantDefinition<T> definition)
        {
            mConstantBufferOffsetMap.emplace(name, mConstantBufferSize);
            mConstantBufferSize += sizeof(ConstantDefinition<T>::Type);
        }

        auto instantiate() -> ProgramInstance&;

        void attachShader(Shader& shader);

    private:
        virtual auto instantiateImpl() const->ProgramInstance* TOV_ABSTRACT;

    protected:
        size_t mConstantBufferSize = 0;
        ProgramState::ConstantBufferOffsetMap mConstantBufferOffsetMap;

        ShaderList mShaders;
        std::vector<std::unique_ptr<ProgramInstance>> mInstances;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif