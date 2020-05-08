#ifndef TOV_RENDERING_PIPELINE_CONSTANT_DEFINITION_H
#define TOV_RENDERING_PIPELINE_CONSTANT_DEFINITION_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    enum class ConstantType
    {
        MATRIX_3,
        MATRIX_4,
        VECTOR_2,
        VECTOR_3,
        VECTOR_4
    };

    template <class T>
    class ConstantDefinition
    {
    public:
        using Type = T;

    public:
        ConstantDefinition(ConstantType type)
            : mType(type)
        {}

        auto getType() const { return mType; }

    private:
        ConstantType mType;

    public:
        static const ConstantDefinition DEFINITION;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
