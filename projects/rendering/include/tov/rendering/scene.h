#ifndef TOV_RENDERING_SCENE_H
#define TOV_RENDERING_SCENE_H

#include "rendering_core.h"

#include "scene_object.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Camera;
	class Entity;

	class Scene
	{
		TOV_MOVABLE_ONLY(Scene)

	public:
		Scene() = default;
		~Scene() = default;

		template<class T, class... U>
		auto create(U&&... args)
		{
			auto sceneObject = std::unique_ptr<T>(
				new T(std::forward<U>(args)...)
			);
			mSceneObjects.push_back(std::move(sceneObject));
			auto ret = mSceneObjects.back().get();
			return static_cast<T*>(ret);
		}

		auto createCamera() -> Camera*;
		auto createEntity() -> Entity*;

	private:
		using SceneObjectList = std::vector<SceneObjectUPtr>;
		SceneObjectList mSceneObjects;
	};

	TOV_NAMESPACE_END // rendering
}

#endif