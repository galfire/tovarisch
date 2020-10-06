#ifndef TOV_RENDERING_PIPELINE_RASTERIZER_STATE_DESCRIPTOR_H
#define TOV_RENDERING_PIPELINE_RASTERIZER_STATE_DESCRIPTOR_H

#include <tov/rendering/rendering_core.h>

#include "cull_mode.h"
#include "vertex_winding.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class RasterizerStateDescriptor
    {
    public:
        void setCullingEnabled(bool enabled) { mCullingEnabled = enabled; }
        auto getCullingEnabled() const { return mCullingEnabled; }

        void setCullMode(pipeline::CullMode cullMode) { mCullMode = cullMode; }
        auto getCullMode() const { return mCullMode; }

        void setVertexWinding(pipeline::VertexWinding vertexWinding) { mVertexWinding = vertexWinding; }
        auto getVertexWinding() const { return mVertexWinding; }

    private:
        bool mCullingEnabled = true;
        CullMode mCullMode = CullMode::BACK;
        VertexWinding mVertexWinding = VertexWinding::COUNTERCLOCKWISE;
    };

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // rendering
}

#endif
