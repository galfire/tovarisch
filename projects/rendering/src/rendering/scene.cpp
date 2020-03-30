#include "rendering/scene.h"

#include "rendering/camera.h"
#include "rendering/entity.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	auto Scene::createCamera() -> Camera&
	{
		auto& camera = *create<Camera>(*this);
		mCameras.push_back(camera);
		return camera;
	}

	auto Scene::createEntity() -> Entity&
	{
		auto& entity = *create<Entity>();
		return entity;
	}

	void Scene::renderCameras()
	{
		for (auto&& camera : mCameras)
		{
			camera.get().render();
		}
	}

	TOV_NAMESPACE_END // rendering
}