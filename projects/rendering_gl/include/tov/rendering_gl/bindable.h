#ifndef TOV_RENDERING_GL_BINDABLE_H
#define TOV_RENDERING_GL_BINDABLE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)

    class Bindable
    {
    public:
        Bindable() = default;
        virtual ~Bindable() = default;

        virtual void bind() const TOV_ABSTRACT;
        virtual void unbind() const TOV_ABSTRACT;
    };

    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
