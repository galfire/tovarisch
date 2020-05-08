#ifndef TOV_RENDERING_PIPELINE_PROGRAM_STATE_H
#define TOV_RENDERING_PIPELINE_PROGRAM_STATE_H

#include <tov/rendering/rendering_core.h>

#include <tov/memory/heap_area.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class ProgramState
    {
        TOV_MOVABLE_ONLY(ProgramState)

    public:
        ProgramState(size_t constantBufferSize)
            : mConstantBufferSize(constantBufferSize)
        {
            mHeapArea = std::make_unique<memory::HeapArea>(mConstantBufferSize);
        }

        ~ProgramState() = default;

        auto getBuffer() const
        {
            return mHeapArea->getStart();
        }

    private:
        size_t mConstantBufferSize = 0;

        std::unique_ptr<memory::HeapArea> mHeapArea;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
