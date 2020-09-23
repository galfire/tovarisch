#ifndef TOV_RENDERING_PIPELINE_STATE_OBJECT_H
#define TOV_RENDERING_PIPELINE_STATE_OBJECT_H

#include <tov/rendering/rendering_core.h>

#include "rasterizer_state_descriptor.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class PipelineStateObject
    {
    public:
        PipelineStateObject(
            RasterizerStateDescriptor rasterizerStateDescriptor
        )
            : mRasterizerStateDescriptor(rasterizerStateDescriptor)
        {}

        auto getRasterizerStateDescriptor() const
        {
            return mRasterizerStateDescriptor;
        }

    private:
        RasterizerStateDescriptor mRasterizerStateDescriptor

    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
