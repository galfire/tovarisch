#ifndef TOV_RENDERING_PIPELINE_CONSTANT_DEFINITION_H
#define TOV_RENDERING_PIPELINE_CONSTANT_DEFINITION_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    template <class T>
    class ConstantDefinition
    {
    public:
        using Type = T;

    public:
        static const ConstantDefinition DEFINITION;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
