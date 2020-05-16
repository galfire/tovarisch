#ifndef TOV_RENDERING_PIPELINE_PROGRAM_H
#define TOV_RENDERING_PIPELINE_PROGRAM_H

#include <tov/rendering/rendering_core.h>

#include "constant_definition.h"
#include "program_instance.h"

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

#include <string>

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
            auto descriptor = ProgramInstance::ConstantDescriptor{ static_cast<ptrdiff_t>(mConstantBufferSize), definition.getType() };
            mConstantBufferDescriptorMap.emplace(name, descriptor);
            mConstantBufferSize += sizeof(typename ConstantDefinition<T>::Type);
        }

        auto instantiate() -> ProgramInstance&;

        void attachShader(Shader& shader);
        void link() const;
        void buildLocationMap();
        void use() const;

        virtual void setInteger(std::string name, int data) const TOV_ABSTRACT;
        virtual void setFloat(std::string name, float data) const TOV_ABSTRACT;

        virtual void setVector2(std::string name, void const* const data) const TOV_ABSTRACT;
        virtual void setVector3(std::string name, void const* const data) const TOV_ABSTRACT;
        virtual void setVector4(std::string name, void const* const data) const TOV_ABSTRACT;
        
        virtual void setMatrix3(std::string name, void const *const data) const TOV_ABSTRACT;
        virtual void setMatrix4(std::string name, void const *const data) const TOV_ABSTRACT;

    private:
        void detachShader(Shader& shader) const;
        virtual void attachShaderImpl(Shader& shader) const TOV_ABSTRACT;
        virtual void detachShaderImpl(Shader& shader) const TOV_ABSTRACT;
        virtual void linkImpl() const TOV_ABSTRACT;
        virtual void buildLocationMapImpl() TOV_ABSTRACT;
        virtual void useImpl() const TOV_ABSTRACT;

    protected:
        size_t mConstantBufferSize = 0;
        ProgramInstance::ConstantBufferDescriptorMap mConstantBufferDescriptorMap;

        ShaderList mShaders;
        std::vector<std::unique_ptr<ProgramInstance>> mInstances;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
