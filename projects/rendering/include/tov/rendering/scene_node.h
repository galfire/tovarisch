#ifndef TOV_RENDERING_SCENE_NODE_H
#define TOV_RENDERING_SCENE_NODE_H

#include "rendering_core.h"

#include "node/node.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class SceneObject;

	class SceneNode
		: public node::Node
	{
	public:
		SceneNode() = default;
		~SceneNode() = default;

		void attachSceneObject(SceneObject* sceneObject);

	private:
		std::vector<SceneObject*> mSceneObjects;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
