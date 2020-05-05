#include <tov/rendering/backend.h>

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
        glClearDepth(1.0f);

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

    void Draw(mesh::DrawData const *const drawData)
    {
        auto& programInstance = drawData->getProgramInstance();
        programInstance.use();

        auto const& ibo = static_cast<buffers::IndexBufferObject const&>(drawData->getIndexBufferObject());
        auto const& vbo = static_cast<buffers::VertexBufferObject const&>(drawData->getVertexBufferObject());

        using Buffer = rendering::gl::buffers::Buffer<buffers::UsageSettings::STATIC, buffers::AccessSettings::WRITE>;
        auto& indexBuffer = static_cast<Buffer&>(ibo.getBuffer());
        auto& vertexBuffer = static_cast<Buffer&>(vbo.getBuffer());

        // TODO: Abstract and make a persistent VAO
        GLuint vao;
        {
            auto op = log_gl_op("generate and bind VAO");
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

        }
        
        // Bind the index and vertex buffer before drawing
        auto bindIndex = indexBuffer.bind();
        auto bindVertex = vertexBuffer.bind();

        auto vbf = vbo.getBufferFormat();
        auto desc = vbf.getDescriptor();

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

        GLenum type = 0;
        switch (ibo.getIndexType())
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
            auto op = log_gl_op("draw elements", ibo.getNumIndices(), getEnumString(type));
            glDrawElements(
                GL_TRIANGLES,
                ibo.getNumIndices(),
                type,
                0
            );
        }

        for (auto&& a : desc.attributeDescriptors)
        {
            auto location = a.location;
            auto op = log_gl_op("disable vertex attrib", location);
            glDisableVertexAttribArray(location);
        }

        glDeleteVertexArrays(1, &vao);
    }

    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}
