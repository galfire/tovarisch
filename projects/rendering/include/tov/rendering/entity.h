#ifndef TOV_RENDERING_ENTITY_H
#define TOV_RENDERING_ENTITY_H

#include "rendering_core.h"

#include "scene_object.h"

#include "component.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class MeshComponent;

	TOV_NAMESPACE_BEGIN(mesh)

	class Mesh;

	TOV_NAMESPACE_END //mesh

	class Entity
		: public SceneObject
	{
		TOV_MOVABLE_ONLY(Entity)

	public:
		Entity() = default;
		~Entity() = default;

		template<class T, class... U>
		T* create(U&&... args)
		{
			auto component = std::unique_ptr<T>(
				new T(std::forward<U>(args)...)
			);
			mComponents.push_back(std::move(component));
			auto ret = mComponents.back().get();
			return static_cast<T*>(ret);
		}

		MeshComponent* createMeshComponent(mesh::Mesh& mesh);

	private:
		using ComponentList = std::vector<ComponentUPtr>;
		ComponentList mComponents;
	};

	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_ENTITY_H
