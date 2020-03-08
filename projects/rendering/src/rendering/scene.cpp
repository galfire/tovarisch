#include "rendering/scene.h"

#include "rendering/camera.h"
#include "rendering/entity.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	auto Scene::createCamera() -> Camera*
	{
		return create<Camera>();
	}

	auto Scene::createEntity() -> Entity*
	{
		return create<Entity>();
	}

	TOV_NAMESPACE_END // rendering
}