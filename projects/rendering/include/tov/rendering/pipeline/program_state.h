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
        TOV_NON_COPYABLE(ProgramState)

    private:
        auto getConstantOffset(const char* name) const
        {
            return mConstantMap.at(name);
        }

        auto getConstantLocation(const char* name) const
        {
            auto buffer = static_cast<byte*>(mHeapArea->getStart());
            auto location = buffer + getConstantOffset(name);
            return location;
        }

    public:
        ProgramState() = default;
        ~ProgramState() = default;

        void initialize()
        {
            mHeapArea = std::make_unique<memory::HeapArea>(mBufferSize);
        }

        template<class T>
        void addConstantDefinition(const char* name, ConstantDefinition<T> definition)
        {
            mConstantMap.emplace(name, mBufferSize);
            mBufferSize += sizeof(ConstantDefinition<T>::Type);
        }

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
        size_t mBufferSize = 0;
        std::unique_ptr<memory::HeapArea> mHeapArea;
        using ConstantMap = std::unordered_map<std::string, ptrdiff_t>;
        ConstantMap mConstantMap;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
