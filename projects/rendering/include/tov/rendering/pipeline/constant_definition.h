#ifndef TOV_RENDERING_PIPELINE_CONSTANT_DEFINITION_H
#define TOV_RENDERING_PIPELINE_CONSTANT_DEFINITION_H

#include <tov/rendering/rendering_core.h>

#include "constant_type.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    template <ConstantType C, class T>
    class ConstantDefinition
    {
    public:
        using Type = T;

    public:
        ConstantDefinition() = default;
        ~ConstantDefinition() = default;

        auto getConstantType() const { return C; }

    public:
        static const ConstantDefinition DEFINITION;
    };

    template <ConstantType C, class T>
    const ConstantDefinition<C, T> ConstantDefinition<C, T>::DEFINITION = ConstantDefinition<C, T>();

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
