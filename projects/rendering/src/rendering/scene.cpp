#include "rendering/scene.h"

#include "rendering/camera.h"
#include "rendering/draw_context.h"
#include "rendering/entity.h"
#include "rendering/render_system.h"
#include "rendering/scene_node.h"
#include "rendering/scene_object.h"
#include "rendering/viewport.h"

#include "rendering/commands/commands.h"
#include "rendering/commands/command_bucket.h"

#include "rendering/mesh/draw_data_context.h"

#include "rendering/backend.h"

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

    Scene::~Scene() noexcept
    {}

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

    void Scene::queue()
    {
        auto& bucket = mRenderSystem.getGBufferBucket();
        auto programInstance = mRenderSystem.getProgramInstanceGBuffer();

        for (auto&& camera : mCameras)
        {
            auto drawContext = DrawContext{};
            camera.get().populateDrawContext(drawContext);

            auto& nodes = drawContext.getSceneNodes();
            auto const& viewMatrix = camera.get().getViewMatrix();

            auto& viewports = camera.get().getViewports();
            for (auto&& viewport : viewports)
            {
                auto width = static_cast<float>(viewport->getWidth());
                auto height = static_cast<float>(viewport->getHeight());
                auto aspectRatio = width / height;
                camera.get().setAspectRatio(aspectRatio);
                auto const& projectionMatrix = camera.get().getProjectionMatrix();

                {
                    auto& command = bucket.addCommand<commands::ApplyViewport>(viewport->getZIndex());
                    command.viewport = viewport;
                }

                {
                    auto& command = bucket.addCommand<commands::ClearViewport>(viewport->getZIndex());
                    command.viewport = viewport;
                }

                auto* drawDataContext = backend::createDrawDataContext();
                auto& startDrawDataContext = bucket.addCommand<commands::StartDrawDataContext>(0);
                startDrawDataContext.drawDataContext = drawDataContext;

                for (auto&& node : nodes)
                {
                    auto const& modelMatrix = node->getTransform().getHomogeneousMatrix();

                    auto const& sceneObjects = node->getSceneObjects();
                    for (auto&& sceneObject : sceneObjects)
                    {
                        auto& drawDataList = sceneObject->getDrawDataList();
                        auto drawDataListSize = drawDataList.size();
                        if (drawDataListSize < 1)
                            continue;

                        /*auto* drawDataContext = backend::createDrawDataContext();
                        auto& startDrawDataContext = bucket.addCommand<commands::StartDrawDataContext>(0);
                        startDrawDataContext.drawDataContext = drawDataContext;*/

                        for (auto&& drawData : drawDataList)
                        {
                            auto& command = bucket.addCommand<commands::Draw>(0);
                            command.modelMatrix = modelMatrix;
                            command.viewMatrix = viewMatrix;
                            command.projectionMatrix = projectionMatrix;
                            command.programInstance = programInstance;
                            command.drawData = &drawData;
                        }
                    }
                }

                auto& endDrawDataContext = bucket.addCommand<commands::EndDrawDataContext>(0);
                endDrawDataContext.drawDataContext = drawDataContext;
            }
        }
    }

    TOV_NAMESPACE_END // rendering
}
