#include <rendering/pipeline/constant_definition.h>

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    template<> const ConstantDefinition<ConstantType::FLOAT, float> ConstantDefinition<ConstantType::FLOAT, float>::DEFINITION;
    template<> const ConstantDefinition<ConstantType::INT, int> ConstantDefinition<ConstantType::INT, int>::DEFINITION;
    
    template<> const ConstantDefinition<ConstantType::MATRIX_3, math::Matrix3> ConstantDefinition<ConstantType::MATRIX_3, math::Matrix3>::DEFINITION;
    template<> const ConstantDefinition<ConstantType::MATRIX_4, math::Matrix4> ConstantDefinition<ConstantType::MATRIX_4, math::Matrix4>::DEFINITION;
    
    template<> const ConstantDefinition<ConstantType::TEXTURE_2D, int> ConstantDefinition<ConstantType::TEXTURE_2D, int>::DEFINITION;
    template<> const ConstantDefinition<ConstantType::TEXTURE_3D, int> ConstantDefinition<ConstantType::TEXTURE_3D, int>::DEFINITION;

    template<> const ConstantDefinition<ConstantType::VECTOR_2, math::Vector2> ConstantDefinition<ConstantType::VECTOR_2, math::Vector2>::DEFINITION;
    template<> const ConstantDefinition<ConstantType::VECTOR_3, math::Vector3> ConstantDefinition<ConstantType::VECTOR_3, math::Vector3>::DEFINITION;
    template<> const ConstantDefinition<ConstantType::VECTOR_4, math::Vector4> ConstantDefinition<ConstantType::VECTOR_4, math::Vector4>::DEFINITION;

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
