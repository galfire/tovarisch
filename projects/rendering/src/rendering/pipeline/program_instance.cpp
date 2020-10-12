#include <rendering/pipeline/program_instance.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    void ProgramInstance::uploadConstants() const
    {
        for (auto&& name : mCPUBuffer.getConstantNames())
        {
            uploadConstant(name);
        }
    }

    void ProgramInstance::uploadConstant(std::string name) const
    {
        auto constantLocation = mCPUBuffer.getConstantLocation(name);
        uploadConstantData(name, constantLocation);
    }

    void ProgramInstance::uploadConstantData(std::string name, void const *const data) const
    {
        auto type = mCPUBuffer.getConstantType(name);
        switch (type)
        {
        case ConstantType::FLOAT:
            mProgram.setFloat(name, *static_cast<float const *const>(data));
            break;
        case ConstantType::INT:
            mProgram.setInteger(name, *static_cast<int const *const>(data));
            break;
        case ConstantType::MATRIX_3:
            break;
        case ConstantType::MATRIX_4:
            mProgram.setMatrix4(name, data);
            break;
        case ConstantType::TEXTURE_2D:
            mProgram.setInteger(name, *static_cast<int const *const>(data));
            break;
        case ConstantType::TEXTURE_3D:
            mProgram.setInteger(name, *static_cast<int const *const>(data));
            break;
        case ConstantType::VECTOR_2:
            mProgram.setVector2(name, data);
            break;
        case ConstantType::VECTOR_3:
            mProgram.setVector3(name, data);
            break;
        case ConstantType::VECTOR_4:
            mProgram.setVector4(name, data);
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
