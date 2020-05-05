#include <rendering/pipeline/constant_definition.h>

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    const ConstantDefinition<math::Matrix4> ConstantDefinition<math::Matrix4>::DEFINITION;
    const ConstantDefinition<math::Matrix3> ConstantDefinition<math::Matrix3>::DEFINITION;
    
    const ConstantDefinition<math::Vector4> ConstantDefinition<math::Vector4>::DEFINITION;
    const ConstantDefinition<math::Vector3> ConstantDefinition<math::Vector3>::DEFINITION;

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
