#include "rendering/render_system.h"

#include "rendering/pixel_format.h"
#include "rendering/render_window.h"
#include "rendering/window_platform_support.h"

#include "rendering/buffers/buffer_manager.h"
#include "rendering/buffers/pixel_buffer_object.h"

#include "rendering/pipeline/constant_type.h"
#include "rendering/pipeline/constant_definition.h"
#include "rendering/pipeline/framebuffer.h"
#include "rendering/pipeline/program.h"
#include "rendering/pipeline/shader.h"

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
        mBufferManager = backend::createBufferManager();
    }

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
        auto size = width * height * pixelFormat.getSize();
        {
            auto& pb = *mBufferManager->createPixelUnpackBuffer(pixelFormat, size);
            auto& pbo = buffers::PixelBufferObject(pb, pixelFormat);
            mTexturePosition = backend::createTexture2D(pbo, width, height, pixelFormat);
            mFramebufferGBuffer->attachTexture(mTexturePosition, pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_0);
        }
        {
            auto& pb = *mBufferManager->createPixelUnpackBuffer(pixelFormat, size);
            auto& pbo = buffers::PixelBufferObject(pb, pixelFormat);
            mTextureNormal = backend::createTexture2D(pbo, width, height, pixelFormat);
            mFramebufferGBuffer->attachTexture(mTextureNormal, pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_1);
        }
        {
            auto& pb = *mBufferManager->createPixelUnpackBuffer(pixelFormat, size);
            auto& pbo = buffers::PixelBufferObject(pb, pixelFormat);
            mTextureAlbedo = backend::createTexture2D(pbo, width, height, pixelFormat);
            mFramebufferGBuffer->attachTexture(mTextureAlbedo, pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_2);
        }

        using CType = pipeline::ConstantType;
        using Matrix4 = tov::math::Matrix4;
        auto MAT_4 = tov::rendering::pipeline::ConstantDefinition<CType::MATRIX_4, Matrix4>::DEFINITION;
        auto TEX_2D = tov::rendering::pipeline::ConstantDefinition<CType::TEXTURE_2D, int>::DEFINITION;

        auto shaderVertexGBuffer = backend::createShader(pipeline::ShaderType::VERTEX, "./shaders/vertex.vert.glsl");
        auto shaderFragmentGBuffer = backend::createShader(pipeline::ShaderType::FRAGMENT, "./shaders/gbuffer.frag.glsl");

        shaderVertexGBuffer->compile();
        shaderFragmentGBuffer->compile();

        mProgramGBuffer = backend::createProgram();
        mProgramGBuffer->attachShader(*shaderVertexGBuffer);
        mProgramGBuffer->attachShader(*shaderFragmentGBuffer);
        mProgramGBuffer->link();
        mProgramGBuffer->addConstantDefinition("modelMatrix", MAT_4);
        mProgramGBuffer->addConstantDefinition("viewMatrix", MAT_4);
        mProgramGBuffer->addConstantDefinition("projectionMatrix", MAT_4);
        mProgramGBuffer->addConstantDefinition("albedoTexture", TEX_2D);
        mProgramGBuffer->addConstantDefinition("normalTexture", TEX_2D);
        mProgramGBuffer->buildLocationMap();

        mProgramInstanceGBuffer = &mProgramGBuffer->instantiate();
        mProgramInstanceGBuffer->setConstant<int>("albedoTexture", 0);
        mProgramInstanceGBuffer->setConstant<int>("normalTexture", 1);
    }

    void RenderSystem::swapBuffers()
    {
        mRenderTargetManager.swapBuffers();
    }

    void RenderSystem::renderFrame()
    {
        mWindowPlatformSupport.messageHandler();

        //mFramebufferGBuffer->bind();

        //mFramebufferDefault->bind();

        mProgramInstanceGBuffer->use();

        mGBufferBucket.submit();

        //mFramebufferDefault->bind();
    }

    TOV_NAMESPACE_END // rendering
}
