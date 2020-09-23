#ifndef TOV_RENDERING_PIPELINE_CONSTANT_TYPE_H
#define TOV_RENDERING_PIPELINE_CONSTANT_TYPE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    enum class ConstantType
    {
        FLOAT,
        INT,
        MATRIX_3,
        MATRIX_4,
        TEXTURE_2D,
        TEXTURE_3D,
        VECTOR_2,
        VECTOR_3,
        VECTOR_4
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
