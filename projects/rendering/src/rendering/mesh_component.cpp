#include "rendering/mesh_component.h"

#include "rendering/mesh/mesh.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	MeshComponent::MeshComponent(mesh::MeshBase& mesh)
		: Component()
		, mMesh(mesh)
	{}

	TOV_NAMESPACE_END // rendering
}