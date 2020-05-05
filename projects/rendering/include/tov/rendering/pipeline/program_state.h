#ifndef TOV_RENDERING_PIPELINE_PROGRAM_STATE_H
#define TOV_RENDERING_PIPELINE_PROGRAM_STATE_H

#include <tov/rendering/rendering_core.h>

#include "constant_definition.h"

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

#include <tov/memory/heap_area.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class ProgramState
    {
        TOV_MOVABLE_ONLY(ProgramState)

    public:
        using ConstantBufferOffsetMap = std::unordered_map<std::string, ptrdiff_t>;

    private:
        auto getConstantOffset(const char* name) const
        {
            return mConstantBufferOffsetMap.at(name);
        }

        auto getConstantLocation(const char* name) const
        {
            auto buffer = mHeapArea->getStart();
            auto location = static_cast<byte*>(buffer) + getConstantOffset(name);
            return location;
        }

    public:
        ProgramState(size_t constantBufferSize, ConstantBufferOffsetMap const& constantBufferOffsetMap)
            : mConstantBufferSize(constantBufferSize)
            , mConstantBufferOffsetMap(constantBufferOffsetMap)
        {
            mHeapArea = std::make_unique<memory::HeapArea>(mConstantBufferSize);
        }

        ~ProgramState() = default;

        template <class T>
        auto getConstant(const char* name) const -> auto const&
        {
            void* ptr = getConstantLocation(name);
            return *static_cast<T*>(ptr);
        }

        template <class T>
        auto setConstant(const char* name, const T& value)
        {
            void* ptr = getConstantLocation(name);
            memcpy(ptr, &value, sizeof(T));
        }

    private:
        size_t mConstantBufferSize = 0;
        ConstantBufferOffsetMap mConstantBufferOffsetMap;

        std::unique_ptr<memory::HeapArea> mHeapArea;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
