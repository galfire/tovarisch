#ifndef TOV_RENDERING_PIPELINE_PROGRAM_INSTANCE_H
#define TOV_RENDERING_PIPELINE_PROGRAM_INSTANCE_H

#include <tov/rendering/rendering_core.h>

#include "constant_definition.h"
#include "program_state.h"

#include <string>
#include <unordered_map>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Program;
    class Shader;

    class ProgramInstance
    {
        TOV_MOVABLE_ONLY(ProgramInstance)

    public:
        struct ConstantDescriptor
        {
            ptrdiff_t offset;
            ConstantType type;
        };

        using ConstantBufferDescriptorMap = std::unordered_map<std::string, ConstantDescriptor>;

    private:
        auto getConstantDescriptor(std::string name) const
        {
            return mConstantBufferDescriptorMap.at(name);
        }

        auto getConstantOffset(std::string name) const
        {
            return getConstantDescriptor(name).offset;
        }

        auto getConstantLocation(std::string name) const
        {
            auto buffer = mProgramState.getBuffer();
            auto location = static_cast<byte*>(buffer) + getConstantOffset(name);
            return location;
        }

        auto getConstantType(std::string name) const
        {
            return getConstantDescriptor(name).type;
        }

    public:
        ProgramInstance(
            Program const& program,
            size_t constantBufferSize,
            ConstantBufferDescriptorMap const& constantBufferDescriptorMap
        )
            : mProgram(program)
            , mProgramState(constantBufferSize)
            , mConstantBufferDescriptorMap(constantBufferDescriptorMap)
            , mConstantNames(std::vector<std::string> {})
        {
            mConstantNames.reserve(mConstantBufferDescriptorMap.size());
            for (auto&& kv : mConstantBufferDescriptorMap)
            {
                mConstantNames.push_back(kv.first);
            }
        }

        ~ProgramInstance() = default;

        template <class T>
        auto setConstant(const char* name, T const value)
        {
            void* ptr = getConstantLocation(name);
            memcpy(ptr, &value, sizeof(T));
        }

        void uploadConstants() const;
        void uploadConstant(std::string name) const;
        void uploadConstantData(std::string name, void const *const data) const;

        void use() const;
        
    private:
        Program const& mProgram;
        ProgramState mProgramState;
        ConstantBufferDescriptorMap mConstantBufferDescriptorMap;
        std::vector<std::string> mConstantNames;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
