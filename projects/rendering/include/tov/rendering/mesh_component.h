#ifndef TOV_RENDERING_MESH_COMPONENT_H
#define TOV_RENDERING_MESH_COMPONENT_H

#include "rendering_core.h"

#include "component.h"
#include "mesh/mesh_instance.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	class Mesh;

	TOV_NAMESPACE_END // mesh

	class MeshComponent
		: public Component
	{
	public:
		MeshComponent(mesh::Mesh& mesh);
		~MeshComponent() = default;

		auto getMeshInstance() const -> auto const& { return mMeshInstance; }

	private:
		mesh::Mesh& mMesh;
		mesh::MeshInstance mMeshInstance;
	};

	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_COMPONENT_H
