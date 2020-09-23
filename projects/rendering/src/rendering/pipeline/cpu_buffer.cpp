#include "rendering/pipeline/cpu_buffer.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    CPUBuffer::CPUBuffer(CPUBufferDescriptor descriptor) noexcept
        : mDescriptor(descriptor)
        , mConstantDescriptorMap(mDescriptor.getConstantDescriptorMap())
    {
        auto size = descriptor.getSize();
        mHeapArea = std::make_unique<memory::HeapArea>(size);

        mConstantNames.reserve(getConstantDescriptorMap().size());
        for (auto&& kv : mConstantDescriptorMap)
        {
            mConstantNames.push_back(kv.first);
        }
    }

    CPUBuffer::~CPUBuffer() noexcept
    {}


    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}
