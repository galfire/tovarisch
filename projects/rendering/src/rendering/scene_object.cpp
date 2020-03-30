#include "rendering/scene_object.h"

#include "rendering/scene_node.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    void SceneObject::attachToSceneNode(SceneNode* sceneNode)
    {
        mParentSceneNode = sceneNode;
    }

    TOV_NAMESPACE_END // rendering
}
