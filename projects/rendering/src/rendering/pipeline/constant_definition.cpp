#include <rendering/pipeline/constant_definition.h>

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    template<> const ConstantDefinition<math::Matrix3> ConstantDefinition<math::Matrix3>::DEFINITION(ConstantType::MATRIX_3);
    template<> const ConstantDefinition<math::Matrix4> ConstantDefinition<math::Matrix4>::DEFINITION(ConstantType::MATRIX_4);
    
    template<> const ConstantDefinition<math::Vector2> ConstantDefinition<math::Vector2>::DEFINITION(ConstantType::VECTOR_2);
    template<> const ConstantDefinition<math::Vector3> ConstantDefinition<math::Vector3>::DEFINITION(ConstantType::VECTOR_3);
    template<> const ConstantDefinition<math::Vector4> ConstantDefinition<math::Vector4>::DEFINITION(ConstantType::VECTOR_4);

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
