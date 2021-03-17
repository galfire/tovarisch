#ifndef TOV_RENDERING_MESH_DRAW_DATA_CONTEXT_H
#define TOV_RENDERING_MESH_DRAW_DATA_CONTEXT_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawDataContext
    {
    public:
        DrawDataContext() = default;
        virtual ~DrawDataContext() {};

        virtual void start() const TOV_ABSTRACT;
        virtual void end() const TOV_ABSTRACT;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
