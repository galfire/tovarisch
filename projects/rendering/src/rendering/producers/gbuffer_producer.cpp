#include "rendering/producers/gbuffer_producer.h"

#include "rendering/backend.h"

#include "rendering/render_system.h"

#include "rendering/pipeline/framebuffer.h"
#include "rendering/pipeline/program.h"
#include "rendering/pipeline/shader.h"

#include "rendering/texture/texture.h"

#include <tov/math/matrix.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    namespace
    {
        using CType = pipeline::ConstantType;
        using Matrix4 = tov::math::Matrix4;
        auto MAT_4 = tov::rendering::pipeline::ConstantDefinition<CType::MATRIX_4, Matrix4>::DEFINITION;
        auto TEX_2D = tov::rendering::pipeline::ConstantDefinition<CType::TEXTURE_2D, int>::DEFINITION;
    }

    GBufferProducer::GBufferProducer(RenderSystem& renderSystem, ResourceBucket& resourceBucket) noexcept
        : Producer(resourceBucket)
        , mRenderSystem(renderSystem)
    {
        mFramebuffer = backend::createFramebuffer();

        auto pixelFormat = PixelFormat(8, 8, 8, 8, 0, 0);
        auto width = 800;
        auto height = 600;
        {
            mTexturePosition = &mRenderSystem.createTexture2D(width, height, pixelFormat);
            mFramebuffer->attachTexture(
                static_cast<texture::Texture2D*>(mTexturePosition),
                pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_0
            );
        }
        {
            mTextureNormal = &mRenderSystem.createTexture2D(width, height, pixelFormat);
            mFramebuffer->attachTexture(
                static_cast<texture::Texture2D*>(mTextureNormal),
                pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_1
            );
        }
        {
            mTextureAlbedo = &mRenderSystem.createTexture2D(width, height, pixelFormat);
            mFramebuffer->attachTexture(
                static_cast<texture::Texture2D*>(mTextureAlbedo),
                pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_2
            );
        }

        mProgram = backend::createProgram();
        {
            auto shaderVertex = backend::createShader(pipeline::ShaderType::VERTEX, "./shaders/gbuffer.vert.glsl");
            shaderVertex->compile();
            mProgram->attachShader(*shaderVertex);
            delete shaderVertex;

            auto shaderFragment = backend::createShader(pipeline::ShaderType::FRAGMENT, "./shaders/gbuffer.frag.glsl");
            shaderFragment->compile();
            mProgram->attachShader(*shaderFragment);
            delete shaderFragment;
        }

        mProgram->link();
        mProgram->addConstantDefinition("modelMatrix", MAT_4);
        mProgram->addConstantDefinition("viewMatrix", MAT_4);
        mProgram->addConstantDefinition("projectionMatrix", MAT_4);
        mProgram->addConstantDefinition("albedoTexture", TEX_2D);
        mProgram->addConstantDefinition("normalTexture", TEX_2D);
        mProgram->buildLocationMap();

        mProgramInstance = &mProgram->instantiate();
        mProgramInstance->setConstant<int>("albedoTexture", 0);
        mProgramInstance->setConstant<int>("normalTexture", 1);
    }

    void GBufferProducer::setInputs()
    {
    }

    void GBufferProducer::setOutputs()
    {
        Resource positionTexture = { mTexturePosition, this };
        setOutput("positionTexture", positionTexture);

        Resource normalTexture = { mTextureNormal, this };
        setOutput("normalTexture", normalTexture);

        Resource albedoTexture = { mTextureAlbedo, this };
        setOutput("albedoTexture", albedoTexture);
    }

    void GBufferProducer::render()
    {
        mFramebuffer->bind();
        mProgramInstance->use();
        mCommandBucket.submit();
    }

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}