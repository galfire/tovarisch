#ifndef TOV_RENDERING_BACKEND_H
#define TOV_RENDERING_BACKEND_H

#include "rendering_core.h"

#include <tov/rendering/pixel_format.h>
#include <tov/rendering/mesh/vertex_data.h>
#include <tov/rendering/pipeline/shader_type.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;
    class Viewport;
    class WindowPlatformSupport;
    class WindowRendererSupport;

    TOV_NAMESPACE_BEGIN(buffers)

    class BufferManagerBase;

    TOV_NAMESPACE_END // buffers

    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData;
    class DrawDataContext;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_BEGIN(pipeline)

    class Framebuffer;
    class Program;
    class ProgramState;
    class Shader;

    TOV_NAMESPACE_END //pipeline

    TOV_NAMESPACE_BEGIN(backend)

    void ApplyViewport(Viewport const *const viewport);
    void ClearViewport(Viewport const *const viewport);
    void Draw(mesh::DrawData const *const drawData);

    auto createRenderSystem(
        WindowPlatformSupport& windowPlatformSupport,
        WindowRendererSupport& windowRednererSupport
    ) -> RenderSystem*;

    auto createBufferManager() -> buffers::BufferManagerBase*;
    auto createDrawDataContext(
        const mesh::VertexData& vertexData,
        const mesh::VertexDataFormat& vertexDataFormat
    ) -> mesh::DrawDataContext*;
    auto getDefaultFramebuffer() -> pipeline::Framebuffer*;
    auto createFramebuffer() -> pipeline::Framebuffer*;
    auto createProgram() -> pipeline::Program*;
    auto createShader(pipeline::ShaderType shaderType, const char* sourceFilePath) -> pipeline::Shader*;
    
    TOV_NAMESPACE_END // backend
    TOV_NAMESPACE_END // rendering
}

#endif
