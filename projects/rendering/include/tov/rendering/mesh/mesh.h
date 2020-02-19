#ifndef TOV_RENDERING_MESH_MESH_H
#define TOV_RENDERING_MESH_MESH_H

#include <tov/rendering/rendering_core.h>

#include "submesh.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	class Mesh
	{
		TOV_MOVABLE_ONLY(Mesh)

	public:
		Mesh() = default;
		~Mesh() = default;

		Submesh* createSubmesh();

	private:
		using SubmeshList = std::vector<SubmeshUPtr>;
		SubmeshList mSubmeshes;
	};

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_MESH_H
