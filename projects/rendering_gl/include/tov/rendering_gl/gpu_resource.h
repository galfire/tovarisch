#ifndef TOV_RENDERING_GL_GPU_RESOURCE_H
#define TOV_RENDERING_GL_GPU_RESOURCE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)

    template<class Binder>
    class GPUResource
    {
    public:
        GPUResource() = default;
        virtual ~GPUResource() = default;

        virtual auto bind() const -> Binder TOV_ABSTRACT;
    };

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
