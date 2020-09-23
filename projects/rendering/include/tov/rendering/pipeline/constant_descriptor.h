#ifndef TOV_RENDERING_PIPELINE_CONSTANT_DESCRIPTOR_H
#define TOV_RENDERING_PIPELINE_CONSTANT_DESCRIPTOR_H

#include <tov/rendering/rendering_core.h>

#include "constant_type.h"

#include <string>
#include <unordered_map>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    struct ConstantDescriptor
    {
        ptrdiff_t offset;
        ConstantType type;
    };

    using ConstantDescriptorMap = std::unordered_map<std::string, ConstantDescriptor>;

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
