#ifndef TOV_RENDERING_SCENE_NODE_H
#define TOV_RENDERING_SCENE_NODE_H

#include "rendering_core.h"

#include "node/node.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

        class Camera;
    class SceneObject;

    class SceneNode
        : public node::Node
    {
    public:
        SceneNode() = default;
        ~SceneNode() = default;

        auto createChild()->SceneNode&;

        auto getChildren() const -> auto& { return mChildren; }

        void attachSceneObject(SceneObject* sceneObject);
        auto getSceneObjects() const { return mSceneObjects; }
        auto getSceneObjects() -> auto& { return mSceneObjects; }

    private:
        std::vector<std::unique_ptr<Node>> mChildren;
        std::vector<SceneObject*> mSceneObjects;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
