#include "rendering/scene_node.h"

#include "rendering/scene_object.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	void SceneNode::attachSceneObject(SceneObject* sceneObject)
	{
		mSceneObjects.push_back(sceneObject);
		sceneObject->attachToSceneNode(this);
	}

	TOV_NAMESPACE_END
}
