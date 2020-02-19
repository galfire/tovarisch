#include "rendering/scene.h"

#include "rendering/camera.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	Camera* Scene::createCamera()
	{
		return create<Camera>();
	}

	TOV_NAMESPACE_END // rendering
}