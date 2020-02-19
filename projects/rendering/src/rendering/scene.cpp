#include "rendering/scene.h"

#include "rendering/camera.h"
#include "rendering/entity.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	Camera* Scene::createCamera()
	{
		return create<Camera>();
	}

	Entity* Scene::createEntity()
	{
		return create<Entity>();
	}

	TOV_NAMESPACE_END // rendering
}