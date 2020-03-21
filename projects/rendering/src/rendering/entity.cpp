#include "rendering/entity.h"

#include "rendering/mesh_component.h"
#include "rendering/mesh/mesh.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	MeshComponent* Entity::createMeshComponent(mesh::MeshBase& mesh)
	{
		return create<MeshComponent>(mesh);
	}

	TOV_NAMESPACE_END // rendering
}