#ifndef TOV_RENDERING_BACKEND_DISPATCH_H
#define TOV_RENDERING_BACKEND_DISPATCH_H

#include "rendering_core.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class BackendDispatch
    {
    public:
        static void ApplyViewport(const void* data);
        static void ClearViewport(const void* data);
        static void Draw(const void* data);
    };

    TOV_NAMESPACE_END // rendering
}

#endif
