#include <tov/rendering/backend.h>
#include "rendering_gl/gl_backend.h"

#include <tov/math/matrix.h>

#include <tov/rendering/viewport.h>

#include <tov/rendering/mesh/draw_data.h>
#include <tov/rendering/mesh/vertex_data.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/usage_settings.h>
#include <tov/rendering/buffers/index_buffer_object.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>

#include <tov/rendering/pipeline/program_instance.h>

#include "rendering_gl/render_system.h"

#include "rendering_gl/bindable.h"

#include "rendering_gl/buffers/buffer.h"
#include "rendering_gl/buffers/buffer_manager.h"

#include "rendering_gl/mesh/draw_data_context.h"

#include "rendering_gl/pipeline/framebuffer.h"
#include "rendering_gl/pipeline/program.h"
#include "rendering_gl/pipeline/shader.h"

#include "rendering_gl/texture/texture.h"

#include "rendering_gl/gl_impl.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(backend)

    TOV_NAMESPACE_BEGIN(gl)

    void SetRasterizerState(pipeline::RasterizerStateDescriptor rasterizerStateDescriptor)
    {
        if (rasterizerStateDescriptor.getCullingEnabled())
        {
            glEnable(GL_CULL_FACE);

            switch (rasterizerStateDescriptor.getCullMode())
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

        switch (rasterizerStateDescriptor.getVertexWinding())
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
        auto rasterizerStateDescriptor = drawData->getRasterizerStateDescriptor();
        gl::SetRasterizerState(rasterizerStateDescriptor);

        auto textureUsages = drawData->getTextureUsages();
        for (auto&& textureUsage : textureUsages)
        {
            auto texture = static_cast<rendering::gl::texture::Texture2D const*>(textureUsage.texture);
            auto slot = textureUsage.slot;
            texture->activate(textureUsage.slot);
        }

        {
            auto& context = drawData->getDrawDataContext();
            context.start();

            auto const& ibo = static_cast<buffers::IndexBufferObject const&>(drawData->getIndexBufferObject());
            using Buffer = rendering::gl::buffers::Buffer<buffers::UsageSettings::STATIC, buffers::AccessSettings::WRITE>;
            auto& indexBuffer = static_cast<Buffer&>(ibo.getBuffer());
            auto bindIndex = indexBuffer.binder();

            DrawIndexed(ibo.getNumIndices(), ibo.getIndexType());

            context.end();
        }

        for (auto&& textureUsage : textureUsages)
        {
            auto texture = static_cast<rendering::gl::texture::Texture2D const*>(textureUsage.texture);
            auto slot = textureUsage.slot;
            texture->deactivate(slot);
        }
    }

    auto createRenderSystem(
        WindowPlatformSupport& windowPlatformSupport,
        WindowRendererSupport& windowRednererSupport
    ) -> RenderSystem*
    {
        return new rendering::gl::RenderSystem(windowPlatformSupport, windowRednererSupport);
    }

    auto createBufferManager() -> buffers::BufferManagerBase*
    {
        return new rendering::gl::buffers::BufferManager();
    }

    auto createDrawDataContext(const mesh::VertexData& vertexData) -> mesh::DrawDataContext*
    {
        auto ddc = new rendering::gl::mesh::DrawDataContext();
        
        ddc->start();

        auto format = vertexData.getFormat();
        auto handles = format.getHandles();
        for (auto&& handle : handles)
        {
            auto vbf = format.getVertexBufferFormatForHandle(handle);
            auto vbo = vertexData.getBufferObjectForHandle(handle);

            using Buffer = rendering::gl::buffers::Buffer<buffers::UsageSettings::STATIC, buffers::AccessSettings::WRITE>;
            auto& vertexBuffer = static_cast<Buffer&>(vbo.getBuffer());
            auto bindVertex = vertexBuffer.binder();

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

        ddc->end();

        return ddc;
    }

    auto getDefaultFramebuffer() -> pipeline::Framebuffer*
    {
        return new rendering::gl::pipeline::Framebuffer(true);
    }

    auto createFramebuffer() -> pipeline::Framebuffer*
    {
        return new rendering::gl::pipeline::Framebuffer(false);
    }

    auto createProgram()->pipeline::Program*
    {
        return new rendering::gl::pipeline::Program();
    }

    auto createShader(pipeline::ShaderType shaderType, const char* sourceFilePath)->pipeline::Shader*
    {
        return new rendering::gl::pipeline::Shader(shaderType, sourceFilePath);
    }

    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}
