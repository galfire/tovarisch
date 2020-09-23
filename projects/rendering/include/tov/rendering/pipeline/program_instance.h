#ifndef TOV_RENDERING_PIPELINE_PROGRAM_INSTANCE_H
#define TOV_RENDERING_PIPELINE_PROGRAM_INSTANCE_H

#include <tov/rendering/rendering_core.h>

#include "constant_definition.h"
#include "constant_descriptor.h"

#include "cpu_buffer.h"
#include "cpu_buffer_descriptor.h"

#include <string>
#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Program;

    class ProgramInstance
    {
        TOV_MOVABLE_ONLY(ProgramInstance)

    public:
        ProgramInstance(
            Program const& program,
            CPUBufferDescriptor const& descriptor
        )
            : mProgram(program)
            , mCPUBuffer(descriptor)
        {}

        ~ProgramInstance() = default;

        template <class T>
        auto setConstant(const char* name, T const value)
        {
            mCPUBuffer.setConstant(name, value);
        }

        void uploadConstants() const;
        void uploadConstant(std::string name) const;
        void uploadConstantData(std::string name, void const *const data) const;

        void use() const;
        
    private:
        Program const& mProgram;

        CPUBuffer mCPUBuffer;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
