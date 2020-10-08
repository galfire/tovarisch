#ifndef TOV_RENDERING_GL_MESH_DRAW_DATA_CONTEXT_H
#define TOV_RENDERING_GL_MESH_DRAW_DATA_CONTEXT_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/mesh/draw_data_context.h>

#include "rendering_gl/gl_impl.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(mesh)

    namespace
    {
        namespace base = rendering::mesh;
    }

    class DrawDataContext
        : public base::DrawDataContext
    {
    public:
        DrawDataContext()
        {
            auto op = log_gl_op("generate VAO");
            glGenVertexArrays(1, &mVAO);
        }

        ~DrawDataContext()
        {
            auto op = log_gl_op("delete VAO");
            glDeleteVertexArrays(1, &mVAO);
        }

        void start() const override
        {
            auto op = log_gl_op("bind VAO");
            glBindVertexArray(mVAO);
        }

        void end() const override
        {
            /*auto op = log_gl_op("unbind VAO");
            glBindVertexArray(0);*/
        }

    private:
        GLuint mVAO;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}

#endif
