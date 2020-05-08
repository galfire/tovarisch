#include <rendering/pipeline/program_instance.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    void ProgramInstance::uploadConstants() const
    {
        for (auto&& name : mConstantNames)
        {
            uploadConstant(name);
        }
    }

    void ProgramInstance::uploadConstant(std::string name) const
    {
        auto constantLocation = getConstantLocation(name);
        uploadConstantData(name, constantLocation);
    }

    void ProgramInstance::uploadConstantData(std::string name, void const *const data) const
    {
        auto type = getConstantType(name);
        switch (type)
        {
        case ConstantType::MATRIX_3:
            break;
        case ConstantType::MATRIX_4:
            mProgram.setMatrix4(name, data);
            break;
        case ConstantType::VECTOR_3:
            mProgram.setVector3(name, data);
            break;
        case ConstantType::VECTOR_2:
            mProgram.setVector2(name, data);
            break;
        }
    }

    void ProgramInstance::use() const
    {
        mProgram.use();
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
