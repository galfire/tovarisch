#include "rendering/producers/skybox_producer.h"

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
        using pipeline::ConstantDefinition, pipeline::ConstantType;

        auto MAT_4 = ConstantDefinition<ConstantType::MATRIX_4, math::Matrix4>::DEFINITION;
        auto TEX_2D = ConstantDefinition<ConstantType::TEXTURE_2D, int>::DEFINITION;
    }

    SkyboxProducer::SkyboxProducer(RenderSystem& renderSystem, ResourceBucket& resourceBucket) noexcept
        : Producer(resourceBucket)
        , mRenderSystem(renderSystem)
    {
        mFramebuffer = backend::createFramebuffer();

        auto pixelFormat = PixelFormat(8, 8, 8, 8, 0, 0);
        auto width = 800;
        auto height = 600;
        {
            mTexture = &mRenderSystem.createTexture2D(width, height, pixelFormat);
            mFramebuffer->attachTexture(
                static_cast<texture::Texture2D*>(mTexture),
                pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_0
            );
        }

        mProgram = backend::createProgram();
        {
            auto shaderVertex = backend::createShader(pipeline::ShaderType::VERTEX, "./shaders/skybox.vert.glsl");
            shaderVertex->compile();
            mProgram->attachShader(*shaderVertex);

            auto shaderFragment = backend::createShader(pipeline::ShaderType::FRAGMENT, "./shaders/skybox.frag.glsl");
            shaderFragment->compile();
            mProgram->attachShader(*shaderFragment);

            mProgram->link();
        }

        mProgram->addConstantDefinition("modelMatrix", MAT_4);
        mProgram->addConstantDefinition("viewMatrix", MAT_4);
        mProgram->addConstantDefinition("projectionMatrix", MAT_4);
        mProgram->addConstantDefinition("skyboxTexture", TEX_2D);
        mProgram->buildLocationMap();

        mProgramInstance = &mProgram->instantiate();
        mProgramInstance->setConstant<int>("skyboxTexture", 0);
    }

    void SkyboxProducer::setInputs()
    {
    }

    void SkyboxProducer::setOutputs()
    {
        setOutput("skyboxTexture", mTexture);
    }

    void SkyboxProducer::render()
    {
        mFramebuffer->bind();
        mProgramInstance->use();
        mCommandBucket.submit();
    }

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}
