#ifndef TOV_RENDERING_PIPELINE_CPU_BUFFER_H
#define TOV_RENDERING_PIPELINE_CPU_BUFFER_H

#include <tov/rendering/rendering_core.h>

#include <tov/memory/heap_area.h>

#include "constant_descriptor.h"
#include "cpu_buffer_descriptor.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class CPUBuffer
    {
        TOV_MOVABLE_ONLY(CPUBuffer)

    public:
        auto getAddress() const
        {
            return mHeapArea->getStart();
        }

        auto getDescriptor() const
        {
            return mDescriptor;
        }

        auto getConstantDescriptorMap() const
        {
            return mConstantDescriptorMap;
        }

    private:
        auto getConstantDescriptor(std::string name) const
        {
            return getConstantDescriptorMap().at(name);
        }

        auto getConstantOffset(std::string name) const
        {
            return getConstantDescriptor(name).offset;
        }

    public:
        CPUBuffer(CPUBufferDescriptor descriptor) noexcept;
        ~CPUBuffer() noexcept;

        auto getConstantNames() const { return mConstantNames; }

        auto getConstantLocation(std::string name) const
        {
            auto buffer = getAddress();
            auto location = static_cast<byte*>(buffer) + getConstantOffset(name);
            return location;
        }

        auto getConstantType(std::string name) const
        {
            return getConstantDescriptor(name).type;
        }

        template <class T>
        auto setConstant(const char* name, T const value)
        {
            void* ptr = getConstantLocation(name);
            memcpy(ptr, &value, sizeof(T));
        }

    private:
        CPUBufferDescriptor const mDescriptor;
        ConstantDescriptorMap const& mConstantDescriptorMap;

        std::unique_ptr<memory::HeapArea> mHeapArea;

        std::vector<std::string> mConstantNames;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
