#include "rendering/scene.h"

#include "rendering/camera.h"
#include "rendering/draw_context.h"
#include "rendering/entity.h"
#include "rendering/render_system.h"
#include "rendering/scene_node.h"
#include "rendering/viewport.h"
#include "rendering/commands/commands.h"
#include "rendering/commands/command_bucket.h"

#include "rendering/pipeline/program_instance.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Scene::Scene(RenderSystem& renderSystem) noexcept
        : mRenderSystem(renderSystem)
    {
        mRootNode = std::unique_ptr<SceneNode>(
            new SceneNode()
        );
    }

    auto Scene::createCamera() -> Camera&
    {
        auto& camera = *create<Camera>(*this);
        mCameras.push_back(camera);
        return camera;
    }

    auto Scene::createEntity() -> Entity&
    {
        auto& entity = *create<Entity>();
        return entity;
    }

    auto Scene::getRootNode() -> SceneNode&
    {
        return *mRootNode.get();
    }

    void Scene::renderCameras()
    {
        auto& bucket = mRenderSystem.getGBufferBucket();

        for (auto&& camera : mCameras)
        {
            auto drawContext = DrawContext{};
            camera.get().populateDrawContext(drawContext);

            auto nodes = drawContext.getSceneNodes();

            auto& viewports = camera.get().getViewports();

            for (auto&& viewport : viewports)
            {
                {
                    auto width = static_cast<float>(viewport->getWidth());
                    auto height = static_cast<float>(viewport->getHeight());
                    auto aspectRatio = width / height;
                    camera.get().setAspectRatio(aspectRatio);
                }

                {
                    auto& command = bucket.addCommand<commands::ApplyViewport>(viewport->getZIndex());
                    command.viewport = viewport;
                }

                {
                    auto& command = bucket.addCommand<commands::ClearViewport>(viewport->getZIndex());
                    command.viewport = viewport;
                }

                for (auto&& node : nodes)
                {
                    const auto& projectionMatrix = camera.get().getProjectionMatrix();
                    const auto& viewMatrix = camera.get().getViewMatrix();
                    const auto& modelMatrix = node->getTransform().getHomogeneousMatrix();

                    // state = program.getState()
                    // bucket.addCommand<SetShaderState>(state)
                    //   -> at submit time, set all uniforms to the values in state

                    auto const& sceneObjects = node->getSceneObjects();
                    for (auto&& sceneObject : sceneObjects)
                    {
                        auto& drawDataList = sceneObject->getDrawDataList();
                        for (auto&& drawData : drawDataList)
                        {
                            auto& command = bucket.addCommand<commands::Draw>(0);
                            command.drawData = &drawData;
                            command.modelMatrix = modelMatrix;
                            command.viewMatrix = viewMatrix;
                            command.projectionMatrix = projectionMatrix;
                        }
                    }
                }
            }
        }
    }

    TOV_NAMESPACE_END // rendering
}
