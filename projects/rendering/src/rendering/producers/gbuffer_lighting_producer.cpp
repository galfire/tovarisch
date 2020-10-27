#include "rendering/producers/gbuffer_lighting_producer.h"

#include "rendering/backend.h"

#include "rendering/render_system.h"

#include "rendering/pipeline/framebuffer.h"
#include "rendering/pipeline/program.h"
#include "rendering/pipeline/shader.h"

#include "rendering/texture/texture.h"

#include "rendering/commands/commands.h"

#include "rendering/mesh/vertex_data_format.h"
#include "rendering/mesh/mesh.h"
#include "rendering/mesh/mesh_instance.h"
#include "rendering/mesh/mesh_manager.h"

#include "rendering/producers/resource_bucket.h"

#include <tov/math/matrix.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    namespace
    {
        using CType = pipeline::ConstantType;
        auto TEX_2D = pipeline::ConstantDefinition<CType::TEXTURE_2D, int>::DEFINITION;
    }

    GBufferLightingProducer::GBufferLightingProducer(RenderSystem& renderSystem, ResourceBucket& resourceBucket) noexcept
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
            auto shaderVertex = backend::createShader(pipeline::ShaderType::VERTEX, "./shaders/pass_through.vert.glsl");
            shaderVertex->compile();
            mProgram->attachShader(*shaderVertex);

            auto shaderFragment = backend::createShader(pipeline::ShaderType::FRAGMENT, "./shaders/gbuffer_lighting.frag.glsl");
            shaderFragment->compile();
            mProgram->attachShader(*shaderFragment);

            mProgram->link();
        }

        mProgram->addConstantDefinition("gPosition", TEX_2D);
        mProgram->addConstantDefinition("gNormal", TEX_2D);
        mProgram->addConstantDefinition("gAlbedo", TEX_2D);
        mProgram->buildLocationMap();

        mProgramInstance = &mProgram->instantiate();
        mProgramInstance->setConstant<int>("gPosition", 0);
        mProgramInstance->setConstant<int>("gNormal", 1);
        mProgramInstance->setConstant<int>("gAlbedo", 2);

        auto& fullscreenQuad = mRenderSystem.getMeshManager()->getFullscreenQuad();
        mFullscreenQuadInstance = &fullscreenQuad.instantiate();
    }

    void GBufferLightingProducer::setInputs()
    {
        setInput("positionTexture");
        setInput("normalTexture");
        setInput("albedoTexture");
    }

    void GBufferLightingProducer::setOutputs()
    {
        setOutput("gBufferLighting", { mTexture });
    }

    void GBufferLightingProducer::render()
    {
        auto* drawDataContext = backend::createDrawDataContext();

        auto& submeshInstance = mFullscreenQuadInstance->getSubmeshInstance(0);

        auto texturePosition = reinterpret_cast<texture::Texture*>(getResource("positionTexture"));
        auto textureNormal = reinterpret_cast<texture::Texture*>(getResource("normalTexture"));
        auto textureAlbedo = reinterpret_cast<texture::Texture*>(getResource("albedoTexture"));

        std::vector<pipeline::TextureDescriptor> textureDescriptors;
        textureDescriptors.emplace_back(texturePosition, 0);
        textureDescriptors.emplace_back(textureNormal, 1);
        textureDescriptors.emplace_back(textureAlbedo, 2);

        pipeline::RasterizerStateDescriptor rasterizerStateDescriptor;

        auto drawData = mesh::DrawData(
            submeshInstance.getIndexBufferObject(),
            submeshInstance.getVertexBufferObjects(),
            textureDescriptors,
            rasterizerStateDescriptor
        );

        {
            auto& command = mCommandBucket.addCommand<commands::StartDrawDataContext>(0);
            command.drawDataContext = drawDataContext;
        }
        {
            auto& command = mCommandBucket.addCommand<commands::UploadConstants>(0);
            command.programInstance = mProgramInstance;
        }
        {
            auto& command = mCommandBucket.addCommand<commands::Draw>(0);
            command.drawData = &drawData;
        }
        {
            auto& command = mCommandBucket.addCommand<commands::EndDrawDataContext>(0);
            command.drawDataContext = drawDataContext;
        }

        mFramebuffer->bind();
        mProgramInstance->use();
        mCommandBucket.submit();
    }

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}
