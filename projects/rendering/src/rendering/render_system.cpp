#include "rendering/render_system.h"

#include "rendering/pixel_format.h"
#include "rendering/render_window.h"
#include "rendering/window_platform_support.h"

#include "rendering/scene.h"

#include "rendering/commands/commands.h"

#include "rendering/buffers/buffer_manager.h"
#include "rendering/buffers/pixel_buffer_object.h"

#include "rendering/geometry/rectangle.h"

#include "rendering/mesh/mesh.h"
#include "rendering/mesh/mesh_instance.h"
#include "rendering/mesh/submesh_instance.h"
#include "rendering/mesh/mesh_manager.h"
#include "rendering/mesh/draw_data.h"

#include "rendering/pipeline/constant_type.h"
#include "rendering/pipeline/constant_definition.h"
#include "rendering/pipeline/framebuffer.h"
#include "rendering/pipeline/program.h"
#include "rendering/pipeline/shader.h"
#include "rendering/pipeline/texture_descriptor.h"
#include "rendering/pipeline/rasterizer_state_descriptor.h"

#include "rendering/texture/texture.h"

#include <tov/math/vector.h>
#include <tov/math/matrix.h>

#include "rendering/backend.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    RenderSystem::RenderSystem(
        WindowPlatformSupport& windowPlatformSupport,
        WindowRendererSupport& windowRendererSupport
    ) noexcept
        : mRenderTargetManager()
        , mWindowPlatformSupport(windowPlatformSupport)
        , mWindowRendererSupport(windowRendererSupport)
    {
        mBufferManager = std::unique_ptr<buffers::BufferManagerBase>(
            backend::createBufferManager()
        );
        mMeshManager = std::unique_ptr<mesh::MeshManager>(
            new mesh::MeshManager(*mBufferManager)
        );
    }

    RenderSystem::~RenderSystem() noexcept
    {}

    auto RenderSystem::createRenderWindow(const char* name, uint width, uint height, bool fullscreen) -> RenderWindow&
    {
        auto renderWindow = mRenderTargetManager.template create<RenderWindow>(
            mWindowPlatformSupport,
            mWindowRendererSupport,
            name,
            width,
            height,
            fullscreen
        );
        return *renderWindow;
    }

    void RenderSystem::initialize()
    {
        mFramebufferDefault = backend::createFramebuffer(true);
        mFramebufferGBuffer = backend::createFramebuffer(false);

        auto pixelFormat = PixelFormat(8, 8, 8, 8, 0, 0);
        auto width = 800;
        auto height = 600;
        {
            mTexturePosition = &createTexture2D(width, height, pixelFormat);
            mFramebufferGBuffer->attachTexture(
                static_cast<texture::Texture2D*>(mTexturePosition),
                pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_0
            );
        }
        {
            mTextureNormal = &createTexture2D(width, height, pixelFormat);
            mFramebufferGBuffer->attachTexture(
                static_cast<texture::Texture2D*>(mTextureNormal),
                pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_1
            );
        }
        {
            mTextureAlbedo = &createTexture2D(width, height, pixelFormat);
            mFramebufferGBuffer->attachTexture(
                static_cast<texture::Texture2D*>(mTextureAlbedo),
                pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_2
            );
        }

        using CType = pipeline::ConstantType;
        using Matrix4 = tov::math::Matrix4;
        auto MAT_4 = tov::rendering::pipeline::ConstantDefinition<CType::MATRIX_4, Matrix4>::DEFINITION;
        auto TEX_2D = tov::rendering::pipeline::ConstantDefinition<CType::TEXTURE_2D, int>::DEFINITION;

        //
        // GBUFFER

        mProgramGBuffer = backend::createProgram();

        {
            auto shaderVertex = backend::createShader(pipeline::ShaderType::VERTEX, "./shaders/gbuffer.vert.glsl");
            shaderVertex->compile();
            mProgramGBuffer->attachShader(*shaderVertex);

            auto shaderFragment = backend::createShader(pipeline::ShaderType::FRAGMENT, "./shaders/gbuffer.frag.glsl");
            shaderFragment->compile();
            mProgramGBuffer->attachShader(*shaderFragment);
        }

        mProgramGBuffer->link();
        // Model data
        mProgramGBuffer->addConstantDefinition("modelMatrix", MAT_4);
        // Camera data
        mProgramGBuffer->addConstantDefinition("viewMatrix", MAT_4);
        mProgramGBuffer->addConstantDefinition("projectionMatrix", MAT_4);
        // GBuffer data
        mProgramGBuffer->addConstantDefinition("albedoTexture", TEX_2D);
        mProgramGBuffer->addConstantDefinition("normalTexture", TEX_2D);

        mProgramGBuffer->buildLocationMap();

        // Binding
        mProgramInstanceGBuffer = &mProgramGBuffer->instantiate();
        mProgramInstanceGBuffer->setConstant<int>("albedoTexture", 0);
        mProgramInstanceGBuffer->setConstant<int>("normalTexture", 1);

        //
        // GBUFFER LIGHTING

        mProgramGBufferLighting = backend::createProgram();

        {
            auto shaderVertex = backend::createShader(pipeline::ShaderType::VERTEX, "./shaders/pass_through.vert.glsl");
            shaderVertex->compile();
            mProgramGBufferLighting->attachShader(*shaderVertex);

            auto shaderFragment = backend::createShader(pipeline::ShaderType::FRAGMENT, "./shaders/gbuffer_lighting.frag.glsl");
            shaderFragment->compile();
            mProgramGBufferLighting->attachShader(*shaderFragment);
        }

        mProgramGBufferLighting->link();
        mProgramGBufferLighting->addConstantDefinition("gPosition", TEX_2D);
        mProgramGBufferLighting->addConstantDefinition("gNormal", TEX_2D);
        mProgramGBufferLighting->addConstantDefinition("gAlbedo", TEX_2D);
        mProgramGBufferLighting->buildLocationMap();

        mProgramInstanceGBufferLighting = &mProgramGBufferLighting->instantiate();
        mProgramInstanceGBufferLighting->setConstant<int>("gPosition", 0);
        mProgramInstanceGBufferLighting->setConstant<int>("gNormal", 1);
        mProgramInstanceGBufferLighting->setConstant<int>("gAlbedo", 2);

        //
        // FULLSCREEN

        auto vertexDataFormat = tov::rendering::mesh::VertexDataFormat();
        {
            tov::rendering::buffers::VertexFormat vf;
            vf.addAttribute(tov::rendering::buffers::VertexAttribute::POSITION, 0);
            vf.addAttribute(tov::rendering::buffers::VertexAttribute::TEXTURE_COORDINATE, 1);
            tov::rendering::buffers::VertexBufferFormat vbf(
                tov::rendering::buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
                vf
            );
            vertexDataFormat.mapHandleToFormat(0, vbf);
        }

        mFullscreenQuad = mMeshManager->create();
        {
            auto geometry = tov::rendering::geometry::Rectangle(2.0f, 2.0f); // [ -1, +1 ], [ -1, +1 ]
            mFullscreenQuad->createSubmesh(geometry, vertexDataFormat);
        }

        mFullscreenQuadInstance = &mFullscreenQuad->instantiate();
    }

    void RenderSystem::swapBuffers()
    {
        mRenderTargetManager.swapBuffers();
    }

    void RenderSystem::renderFrame(Scene& scene)
    {
        mWindowPlatformSupport.messageHandler();

        scene.queue();
        
        //
        // GBuffer Pass

        mFramebufferGBuffer->bind();
        mProgramInstanceGBuffer->use();
        mGBufferBucket.submit();

        //
        // GBuffer Lighting (combine) Pass

        auto* drawDataContext = backend::createDrawDataContext();

        auto& submeshInstance = mFullscreenQuadInstance->getSubmeshInstance(0);

        std::vector<pipeline::TextureDescriptor> textureDescriptors;
        textureDescriptors.emplace_back(mTexturePosition, 0);
        textureDescriptors.emplace_back(mTextureNormal, 1);
        textureDescriptors.emplace_back(mTextureAlbedo, 2);
        
        pipeline::RasterizerStateDescriptor rasterizerStateDescriptor;
        
        auto drawData = mesh::DrawData(
            submeshInstance.getIndexBufferObject(),
            submeshInstance.getVertexBufferObjects(),
            textureDescriptors,
            rasterizerStateDescriptor
        );

        {
            auto& command = mGBufferLightingBucket.addCommand<commands::StartDrawDataContext>(0);
            command.drawDataContext = drawDataContext;
        }
        {
            auto& command = mGBufferLightingBucket.addCommand<commands::UploadConstants>(0);
            command.programInstance = mProgramInstanceGBufferLighting;
        }
        {
            auto& command = mGBufferLightingBucket.addCommand<commands::Draw>(0);
            command.drawData = &drawData;
        }
        {
            auto& command = mGBufferLightingBucket.addCommand<commands::EndDrawDataContext>(0);
            command.drawDataContext = drawDataContext;
        }
        
        mFramebufferDefault->bind();
        mProgramInstanceGBufferLighting->use();
        mGBufferLightingBucket.submit();
    }

    TOV_NAMESPACE_END // rendering
}
