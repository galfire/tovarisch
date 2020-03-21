#ifndef TOV_RENDERING_MESH_COMPONENT_H
#define TOV_RENDERING_MESH_COMPONENT_H

#include "rendering_core.h"

#include "component.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	TOV_NAMESPACE_BEGIN(mesh)

	class MeshBase;

	TOV_NAMESPACE_END // mesh

	class MeshComponent
		: public Component
	{
	public:
		MeshComponent(mesh::MeshBase& mesh);
		~MeshComponent() = default;

	private:
		mesh::MeshBase& mMesh;
	};

	TOV_NAMESPACE_END
}

#endif // !TOV_RENDERING_MESH_COMPONENT_H
