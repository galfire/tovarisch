#ifndef TOV_RENDERING_PIPELINE_CPU_BUFFER_DESCRIPTOR_H
#define TOV_RENDERING_PIPELINE_CPU_BUFFER_DESCRIPTOR_H

#include <tov/rendering/rendering_core.h>

#include "constant_descriptor.h"
#include "constant_definition.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class CPUBufferDescriptor
    {
    public:
        template<ConstantType C, class T>
        void addConstantDefinition(const char* name, ConstantDefinition<C, T> definition)
        {
            auto descriptor = ConstantDescriptor{ static_cast<ptrdiff_t>(mSize), definition.getConstantType() };
            mConstantDescriptorMap.emplace(name, descriptor);
            mSize += sizeof(typename ConstantDefinition<C, T>::Type);
        }

        auto getSize() const { return mSize; }
        auto getConstantDescriptorMap() const -> auto& { return mConstantDescriptorMap; }

    private:
        size_t mSize = 0;
        ConstantDescriptorMap mConstantDescriptorMap;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
