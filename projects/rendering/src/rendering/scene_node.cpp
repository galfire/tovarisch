#include "rendering/scene_node.h"

#include "rendering/scene_object.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    auto SceneNode::createChild() -> SceneNode&
    {
        auto child = std::unique_ptr<SceneNode>(
            new SceneNode()
        );
        mChildren.push_back(std::move(child));
        auto ret = mChildren.back().get();
        return *static_cast<SceneNode*>(ret);
    }

    void SceneNode::attachSceneObject(SceneObject* sceneObject)
    {
        mSceneObjects.push_back(sceneObject);
        sceneObject->attachToSceneNode(this);
    }

    TOV_NAMESPACE_END
}
