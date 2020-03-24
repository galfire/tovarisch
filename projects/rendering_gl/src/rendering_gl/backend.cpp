#include <tov/rendering/backend.h>

#include "rendering_gl/gl_impl.h"

#include <tov/rendering/viewport.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(backend)

    void ApplyViewport(Viewport* viewport)
    {
        GLsizei x, y, w, h;
        
        x = viewport->getLeft();
        y = viewport->getTop();
        w = viewport->getWidth();
        h = viewport->getHeight();
        
        ::glViewport(x, y, w, h);
        
        ::glScissor(x, y, w, h);
        ::glEnable(GL_SCISSOR_TEST);
        
        GLbitfield flags = 0;
        
        flags |= GL_COLOR_BUFFER_BIT;

        auto colour = viewport->getBackgroundColour();
        ::glClearColor(
        	colour.r,
        	colour.g,
        	colour.b,
        	colour.a
        );
        
        flags |= GL_DEPTH_BUFFER_BIT;
        //glClearDepth(1.0f);
        
        flags |= GL_STENCIL_BUFFER_BIT;
        
        ::glClear(flags);
    }

    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}
