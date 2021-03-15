#include "rendering/producers/fullscreen_producer.h"

#include "rendering/backend.h"

#include "rendering/render_system.h"

#include "rendering/pipeline/framebuffer.h"
#include "rendering/pipeline/program.h"
#include "rendering/pipeline/shader.h"

#include "rendering/texture/texture.h"

#include "rendering/commands/commands.h"

#include "rendering/geometry/rectangle.h"

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
        using pipeline::ConstantDefinition, pipeline::ConstantType;
        auto TEX_2D = ConstantDefinition<ConstantType::TEXTURE_2D, int>::DEFINITION;
    }

    FullscreenProducer::FullscreenProducer(RenderSystem& renderSystem, ResourceBucket& resourceBucket) noexcept
        : Producer(resourceBucket)
        , mRenderSystem(renderSystem)
    {
        mFramebuffer = backend::getDefaultFramebuffer();

        mProgram = backend::createProgram();
        {
            auto shaderVertex = backend::createShader(pipeline::ShaderType::VERTEX, "./shaders/pass_through.vert.glsl");
            shaderVertex->compile();
            mProgram->attachShader(*shaderVertex);

            auto shaderFragment = backend::createShader(pipeline::ShaderType::FRAGMENT, "./shaders/pass_through.frag.glsl");
            shaderFragment->compile();
            mProgram->attachShader(*shaderFragment);

            mProgram->link();
        }

        mProgram->addConstantDefinition("Texture", TEX_2D);
        mProgram->buildLocationMap();

        mProgramInstance = &mProgram->instantiate();
        mProgramInstance->setConstant<int>("Texture", 0);

        auto& fullscreenQuad = mRenderSystem.getMeshManager()->getFullscreenQuad();
        mFullscreenQuadInstance = &fullscreenQuad.instantiate();
    }

    void FullscreenProducer::setInputs()
    {
        setInput("gBufferLighting");
        setInput("skyboxTexture");
    }

    void FullscreenProducer::setOutputs()
    {
    }

    void FullscreenProducer::render()
    {
        auto* drawDataContext = backend::createDrawDataContext();

        auto& submeshInstance = mFullscreenQuadInstance->getSubmeshInstance(0);

        //auto texture = reinterpret_cast<texture::Texture*>(getResource("gBufferLighting"));
        auto texture = reinterpret_cast<texture::Texture*>(getResource("skyboxTexture"));

        std::vector<pipeline::TextureUsage> textureUsages;
        textureUsages.emplace_back(texture, 0);

        pipeline::RasterizerStateDescriptor rasterizerStateDescriptor;

        auto drawData = mesh::DrawData(
            submeshInstance.getIndexBufferObject(),
            submeshInstance.getVertexBufferObjects(),
            textureUsages,
            rasterizerStateDescriptor
        );

        {
            auto& command = mCommandBucket.addCommand<commands::StartDrawDataContext>();
            command.drawDataContext = drawDataContext;
        }
        {
            auto& command = mCommandBucket.addCommand<commands::UploadConstants>();
            command.programInstance = mProgramInstance;
        }
        {
            auto& command = mCommandBucket.addCommand<commands::Draw>();
            command.drawData = &drawData;
        }
        {
            auto& command = mCommandBucket.addCommand<commands::EndDrawDataContext>();
            command.drawDataContext = drawDataContext;
        }

        mFramebuffer->bind();
        mProgramInstance->use();
        mCommandBucket.submit();
    }

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}
