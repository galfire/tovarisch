#ifndef TOV_RENDERING_SCENE_H
#define TOV_RENDERING_SCENE_H

#include "rendering_core.h"

#include "scene_object.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(pipeline)

    class Program;

    TOV_NAMESPACE_END // pipeline

    class Camera;
    class Entity;
    class RenderSystem;
    class SceneNode;

    class Scene
    {
        TOV_MOVABLE_ONLY(Scene)

        using SceneObjectList = std::vector<SceneObjectUPtr>;
        using CameraList = std::vector<std::reference_wrapper<Camera>>;
        using EntityList = std::vector<std::reference_wrapper<Entity>>;

    public:
        Scene(RenderSystem& renderSystem) noexcept;
        ~Scene() noexcept = default;

        template<class T, class... U>
        auto create(U&&... args)
        {
            auto sceneObject = std::unique_ptr<T>(
                new T(std::forward<U>(args)...)
            );
            mSceneObjects.push_back(std::move(sceneObject));
            auto ret = mSceneObjects.back().get();
            return static_cast<T*>(ret);
        }

        auto createCamera() -> Camera&;
        auto createEntity() -> Entity&;

        auto getRootNode() -> SceneNode&;

        void renderCameras(pipeline::Program& program);

    private:
        RenderSystem& mRenderSystem;

        std::unique_ptr<SceneNode> mRootNode;

        SceneObjectList mSceneObjects;
        CameraList mCameras;
        EntityList mEntities;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
