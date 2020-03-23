#include <tov/rendering/backend.h>

#include "rendering_gl/gl_impl.h"

#include <tov/rendering/viewport.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(backend)

    void ApplyViewport()
    {
        std::cout << "APPLYING GL VIEWPORT\n";
    }

    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}
