#ifndef TOV_RENDERING_PIPELINE_PROGRAM_H
#define TOV_RENDERING_PIPELINE_PROGRAM_H

#include <tov/rendering/rendering_core.h>

#include "constant_definition.h"
#include "constant_descriptor.h"
#include "program_instance.h"

#include "cpu_buffer_descriptor.h"

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

        auto getCPUBufferDescriptor() const -> auto& { return mCPUBufferDescriptor; }

        template<ConstantType C, class T>
        void addConstantDefinition(const char* name, ConstantDefinition<C, T> definition)
        {
            mCPUBufferDescriptor.addConstantDefinition(name, definition);
        }

        template<>
        void addConstantDefinition(const char* name, ConstantDefinition<ConstantType::TEXTURE_2D, int> definition)
        {
            mNumTextures2D++;
            mCPUBufferDescriptor.addConstantDefinition(name, definition);
        }

        auto instantiate() -> ProgramInstance&;

        void attachShader(Shader& shader);
        void link() const;
        void buildLocationMap();
        void use() const;

        auto getNumTextures2D() const { return mNumTextures2D; }
        auto getNumTextures3D() const { return mNumTextures3D; }

        virtual void setInteger(std::string name, int data) const TOV_ABSTRACT;
        virtual void setFloat(std::string name, float data) const TOV_ABSTRACT;
        virtual void setVector2(std::string name, void const *const data) const TOV_ABSTRACT;
        virtual void setVector3(std::string name, void const *const data) const TOV_ABSTRACT;
        virtual void setVector4(std::string name, void const *const data) const TOV_ABSTRACT;
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
        uint mNumTextures2D = 0;
        uint mNumTextures3D = 0;

        CPUBufferDescriptor mCPUBufferDescriptor;

        ShaderList mShaders;
        std::vector<std::unique_ptr<ProgramInstance>> mInstances;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
