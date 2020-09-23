#include <tov/rendering/backend.h>
#include "rendering_gl/gl_backend.h"

#include <tov/math/matrix.h>

#include <tov/rendering/viewport.h>

#include <tov/rendering/mesh/draw_data.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/usage_settings.h>
#include <tov/rendering/buffers/index_buffer_object.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>

#include <tov/rendering/pipeline/program_instance.h>

#include "rendering_gl/buffers/buffer.h"

#include "rendering_gl/gl_impl.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(backend)

    TOV_NAMESPACE_BEGIN(gl)

    void SetRasterizerState(pipeline::RasterizerStateDescriptor rasterizerStateDescriptor)
    {
        if (rasterizerStateDescriptor.cullingEnabled)
        {
            glEnable(GL_CULL_FACE);

            switch (rasterizerStateDescriptor.cullMode)
            {
            case pipeline::CullMode::BACK:
                glCullFace(GL_BACK);
                break;
            case pipeline::CullMode::FRONT:
                glCullFace(GL_FRONT);
                break;
            case pipeline::CullMode::FRONT_AND_BACK:
                glCullFace(GL_FRONT_AND_BACK);
                break;
            default:
                glDisable(GL_CULL_FACE);
                break;
            }
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }

        switch (rasterizerStateDescriptor.vertexWinding)
        {
        case pipeline::VertexWinding::CLOCKWISE:
            glFrontFace(GL_CW);
            break;
        case pipeline::VertexWinding::COUNTERCLOCKWISE:
            glFrontFace(GL_CCW);
            break;
        default:
            break;
        }
    }

    TOV_NAMESPACE_END // gl

    void ApplyViewport(Viewport const *const viewport)
    {
        GLsizei x, y, w, h;
        
        x = viewport->getLeft();
        y = viewport->getTop();
        w = viewport->getWidth();
        h = viewport->getHeight();
        
        glViewport(x, y, w, h);
        
        glEnable(GL_SCISSOR_TEST);
        glScissor(x, y, w, h);
    }

    void ClearViewport(Viewport const *const viewport)
    {
        GLbitfield flags = 0;

        flags |= GL_COLOR_BUFFER_BIT;
        auto colour = viewport->getBackgroundColour();
        glClearColor(
            colour.r,
            colour.g,
            colour.b,
            colour.a
        );

        flags |= GL_DEPTH_BUFFER_BIT;
        glClearDepthf(1.0f);

        flags |= GL_STENCIL_BUFFER_BIT;

        glClear(flags);
    }

    auto getEnumString(GLenum e)
    {
        switch (e)
        {
        case GL_FLOAT: return "GL_FLOAT";
        case GL_INT: return "GL_INT";
        case GL_UNSIGNED_INT: return "GL_UNSIGNED_INT";
        case GL_SHORT: return "GL_SHORT";
        case GL_UNSIGNED_SHORT: return "GL_UNSGINED_SHORT";
        case GL_BYTE: return "GL_BYTE";
        case GL_UNSIGNED_BYTE: return "GL_UNSIGNED_BYTE";
        default: return "UNKNOWN";
        }
    }

    void SetIndexBuffer(buffers::IndexBufferObject const& indexBufferObject)
    {

    }
    
    void DrawIndexed(uint numIndices, tov::rendering::buffers::IndexType indexType)
    {
        GLenum type = 0;
        switch (indexType)
        {
        case buffers::IndexType::BITS_8:
            type = GL_UNSIGNED_BYTE;
            break;
        case buffers::IndexType::BITS_16:
            type = GL_UNSIGNED_SHORT;
            break;
        case buffers::IndexType::BITS_32:
            type = GL_UNSIGNED_INT;
            break;
        }

        {
            auto op = log_gl_op("draw elements", numIndices, getEnumString(type));
            glDrawElements(
                GL_TRIANGLES,
                numIndices,
                type,
                0
            );
        }
    }
    
    void Draw(mesh::DrawData const *const drawData)
    {
        // TODO: Abstract and make a persistent VAO
        GLuint vao;
        {
            auto op = log_gl_op("generate and bind VAO");
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
        }

        // Bind the index buffer and vertex buffers before drawing
        using Buffer = rendering::gl::buffers::Buffer<buffers::UsageSettings::STATIC, buffers::AccessSettings::WRITE>;
        
        auto const& ibo = static_cast<buffers::IndexBufferObject const&>(drawData->getIndexBufferObject());
        auto& indexBuffer = static_cast<Buffer&>(ibo.getBuffer());
        auto bindIndex = indexBuffer.bind();

        auto const& vbos = drawData->getVertexBufferObjects();
        for (auto&& vbo_ : vbos)
        {
            auto const& vbo = static_cast<buffers::VertexBufferObject const&>(*vbo_);

            auto& vertexBuffer = static_cast<Buffer&>(vbo.getBuffer());
            auto bindVertex = vertexBuffer.bind();

            auto const& vbf = vbo.getBufferFormat();
            auto const& desc = vbf.getDescriptor();
            for (auto&& a : desc.attributeDescriptors)
            {
                auto location = a.location;
                auto count = a.count;
                auto stride = a.stride;
                auto offset = reinterpret_cast<void*>(a.offset);
                GLenum type = 0;
                switch (a.type)
                {
                case buffers::VertexAttribute::Type::FLOAT:
                    type = GL_FLOAT;
                    break;
                case buffers::VertexAttribute::Type::INT:
                    type = GL_INT;
                    break;
                case buffers::VertexAttribute::Type::UINT:
                    type = GL_UNSIGNED_INT;
                    break;
                case buffers::VertexAttribute::Type::SHORT:
                    type = GL_SHORT;
                    break;
                case buffers::VertexAttribute::Type::USHORT:
                    type = GL_UNSIGNED_SHORT;
                    break;
                case buffers::VertexAttribute::Type::BYTE:
                    type = GL_BYTE;
                    break;
                case buffers::VertexAttribute::Type::UBYTE:
                    type = GL_UNSIGNED_BYTE;
                    break;
                }

                {
                    auto op = log_gl_op("enable vertex attrib", location);
                    glEnableVertexAttribArray(location);
                }

                {
                    auto op = log_gl_op("vertex attrib pointer", location, count, getEnumString(type), false, stride, offset);
                    glVertexAttribPointer(
                        location,
                        count,
                        type,
                        false,
                        stride,
                        offset
                    );
                }
            }
        }

        DrawIndexed(ibo.getNumIndices(), ibo.getIndexType());

        // May not be necessary
        // Vertex attributes are encapsulated by the VAO and will be unset when the VAO is unbound or deleted
        /*for (auto&& vbo_ : vbos)
        {
            auto const& vbo = static_cast<buffers::VertexBufferObject const&>(*vbo_);
            auto const& vbf = vbo.getBufferFormat();
            auto const& desc = vbf.getDescriptor();
            for (auto&& a : desc.attributeDescriptors)
            {
                auto location = a.location;
                auto op = log_gl_op("disable vertex attrib", location);
                glDisableVertexAttribArray(location);
            }
        }*/

        glDeleteVertexArrays(1, &vao);
    }

    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}
