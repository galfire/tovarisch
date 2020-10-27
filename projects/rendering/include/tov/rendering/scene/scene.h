#ifndef TOV_RENDERING_SCENE_SCENE_H
#define TOV_RENDERING_SCENE_SCENE_H

#include <tov/rendering/rendering_core.h>

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Camera;
    class Entity;
    class RenderSystem;
    class SceneNode;
    class SceneObject;

    TOV_NAMESPACE_BEGIN(scene)

    class Skybox;

    class Scene
    {
        TOV_MOVABLE_ONLY(Scene)

    public:
        Scene(RenderSystem& renderSystem) noexcept;
        ~Scene() noexcept;

        template<class T, class... U>
        auto create(U&&... args)
        {
            {
                auto sceneObject = std::unique_ptr<T>(
                    new T(std::forward<U>(args)...)
                );
                mSceneObjects.push_back(std::move(sceneObject));
            }

            auto sceneObject = mSceneObjects.back().get();
            return static_cast<T*>(sceneObject);
        }

        auto createCamera() -> Camera&;
        auto createEntity() -> Entity&;

        auto getRootNode() -> SceneNode&;

        void queue();

        void setSkybox(Skybox* skybox) { mSkybox = skybox; }

    private:
        void queueSkybox();
        void queueGBuffer();

    private:
        RenderSystem& mRenderSystem;

        std::unique_ptr<SceneNode> mRootNode;

        using SceneObjectList = std::vector<std::unique_ptr<SceneObject>>;
        using CameraList = std::vector<std::reference_wrapper<Camera>>;
        using EntityList = std::vector<std::reference_wrapper<Entity>>;

        SceneObjectList mSceneObjects;
        CameraList mCameras;
        EntityList mEntities;

        Skybox* mSkybox;
    };

    TOV_NAMESPACE_END // scene
    TOV_NAMESPACE_END // rendering
}

#endif
