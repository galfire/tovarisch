#include "rendering/mesh_component.h"

#include "rendering/mesh/mesh.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	MeshComponent::MeshComponent(mesh::Mesh& mesh)
		: Component()
		, mMesh(mesh)
		, mMeshInstance(mesh.instantiate())
	{}

	TOV_NAMESPACE_END // rendering
}