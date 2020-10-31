#include "rendering/scene/skybox.h"

#include "rendering/material.h"
#include "rendering/render_system.h"

#include "rendering/mesh/mesh.h"
#include "rendering/mesh/mesh_instance.h"
#include "rendering/mesh/mesh_manager.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(scene)

    Skybox::Skybox(RenderSystem& renderSystem, texture::Texture* texture) noexcept
    {
        auto& cube = renderSystem.getMeshManager()->getCube();
        mCubeInstance = &cube.instantiate();

        auto& submeshInstance = mCubeInstance->getSubmeshInstance(0);

        std::vector<pipeline::TextureUsage> textureUsages;
        textureUsages.emplace_back(texture, 0);

        pipeline::RasterizerStateDescriptor rasterizerStateDescriptor;
        rasterizerStateDescriptor.setCullMode(pipeline::CullMode::FRONT);

        mDrawData = std::unique_ptr<mesh::DrawData>(
            new mesh::DrawData(
                submeshInstance.getIndexBufferObject(),
                submeshInstance.getVertexBufferObjects(),
                textureUsages,
                rasterizerStateDescriptor
            )
        );
    }

    Skybox::~Skybox() noexcept
    {
    }

    TOV_NAMESPACE_END // scene
    TOV_NAMESPACE_END // rendering
}
